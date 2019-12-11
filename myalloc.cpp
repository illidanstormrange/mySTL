#include "myalloc.hpp"

#ifndef __THROW_BAD_ALLOC
#include <iostream>
//#include <unistd.h>
#define __THROW_BAD_ALLOC std::cerr<< "out of memory" << std::endl;exit(1);
#endif

namespace MySTL {
	void(*__alloc_template::__malloc_alloc_oom_handler)() = nullptr;
	void* __alloc_template::oom_malloc(size_t n) {
		void(*my_alloc_handler)();
		void *res;
		while (1) {
			my_alloc_handler = __malloc_alloc_oom_handler;
			if (0 == my_alloc_handler) {
				__THROW_BAD_ALLOC;
			}
			(*my_alloc_handler)();
			res = malloc(n);
			if (res) return res;
		}
	}
	void * __alloc_template::oom_realloc(void *p, size_t n) {
		void(*my_alloc_handler)();
		void *res;
		while (1) {
			my_alloc_handler = __malloc_alloc_oom_handler;
			if (0 == my_alloc_handler) {
				__THROW_BAD_ALLOC;
			}
			res = malloc(n);
			if (res) return res;
		}
	}
	//alloc类的实现
	alloc::obj* alloc::free_list[__NFREELISTS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	char *alloc::start_free = 0;
	char *alloc::end_free = 0;
	size_t alloc::heap_size = 0;
	//1.先判断申请的字节大小是不是大于128字节，是则交给第一级配置器来处理，否继续执行
	//2.找到分配的地质对齐后分配的是第几个大小的链表
	//3.获得该链表之乡的首地址，如果链表没有多余的内存，就先填链表
	//4.返回链表的首地址，和一块能容纳一个对象的内存，并更新链表的首地址
	void *alloc::allocate(size_t n) {
		obj** my_free_list;
		obj* result;

		if (n > static_cast<size_t>(__MAX_BYTES)) {
			return (malloc_alloc::allocate(n));
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if (0 == result) { //没有多余的内存，就先填充链表
			void *r = refill(ROUND_UP(n));
			return r;
		}
		*my_free_list = result->free_list_link;
		return result;
	}
	//其中refill向内存池申请空间的起始地址
	//如果只申请到一个对象的大小，就直接返回一个内存的大小，如果有更多的内存，就继续执行
	//从第二个块内存开始，把从内存池里面分配的内存用链表串起来，并返回一个块内存的地址给用户
	void *alloc::refill(size_t n) {
		int nobjs = 20;
		char *chunk = static_cast<char*>(chunk_alloc(n, nobjs));
		obj** my_free_list;
		if (1 == nobjs) {
			return chunk;
		}
		void *res = chunk;
		my_free_list = free_list + FREELIST_INDEX(n);
		obj* next = (obj*)(chunk + n);
		*my_free_list = next;
		obj* current;
		int i = 1;
		while (1) {
			current = next;
			next = (obj*)((char *)(next)+n);
			if (i != nobjs - 1) {
				current->free_list_link = next;
			}
			else {
				current->free_list_link = next;
				break;
			}
			return res;
			++i;
		}
	}

	void alloc::deallocate(void *p, size_t n)
	{
		obj** my_free_list;
		if (n > static_cast<size_t>(__MAX_BYTES)) {
			malloc_alloc::deallocate(p, n);
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		obj* q = static_cast<obj*>(p);
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}
	//1.内存池的大小大于需要的空间，直接返回起始地址（nobjs默认设置为20，所以每次调用都会给链表额外的19个内存块）
	//2.内存池的内存不足以马上分配那么多的内存，但是还能满足分配一个及以上的大小，那就全部分配出去
	//3.如果一个对象的大小都已经提供不下了，先将零碎的内存块给一个小内存的链表来保存，然后就准备调用malloc申请40块+额
	//  外大小的内存块（额外内存块由heap_size决定），如果申请失败跳转到步骤4，成功跳转到步骤6
	//4.充分利用更大的内存链表，通过递归来调用他们的内存块
	//5.如果还是没有内存块，直接调用一级配置器来申请内存，还是失败就抛出异常，成功申请就继续执行
	//6.重新修改内存的起始地址和结束地址，为当前申请的地址块，重调用chunk_alloc分配内存
	void *alloc::chunk_alloc(size_t size, int &nobjs) {
		char *result;
		size_t total_size = size * nobjs;
		size_t bytes_left = end_free - start_free;

		if (bytes_left >= total_size) {
			result = start_free;
			start_free += total_size;
			return(result);
		}
		else if (bytes_left >= size) {
			nobjs = bytes_left / size;
			total_size = size * nobjs;
			result = start_free;
			start_free += total_size;
			return result;
		}
		else {
			size_t bytes_to_get = 2 * total_size + ROUND_UP(heap_size >> 4);
			if (bytes_left > 0) {
				obj ** my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			start_free = (char*)malloc(bytes_to_get);
			if (0 == start_free) {
				int i;
				obj **my_free_list, *p;
				for (i = size; i <= __MAX_BYTES; i += __ALIGN) {
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (0 != p) {
						*my_free_list = p->free_list_link;
						start_free = (char *)p;
						end_free = start_free + i;
						return chunk_alloc(size, nobjs);
					}
				}
				end_free = 0;
				start_free = (char *)malloc_alloc::allocate(bytes_to_get);
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(size, nobjs);
		}
	}
	void * alloc::reallocate(void* p, size_t old_size, size_t new_size) {
		deallocate(p, old_size);
		p = allocate(new_size);
		return p;
	}

}
