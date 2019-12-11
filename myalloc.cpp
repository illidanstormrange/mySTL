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
	//alloc���ʵ��
	alloc::obj* alloc::free_list[__NFREELISTS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	char *alloc::start_free = 0;
	char *alloc::end_free = 0;
	size_t alloc::heap_size = 0;
	//1.���ж�������ֽڴ�С�ǲ��Ǵ���128�ֽڣ����򽻸���һ�������������������ִ��
	//2.�ҵ�����ĵ��ʶ���������ǵڼ�����С������
	//3.��ø�����֮����׵�ַ���������û�ж�����ڴ棬����������
	//4.����������׵�ַ����һ��������һ��������ڴ棬������������׵�ַ
	void *alloc::allocate(size_t n) {
		obj** my_free_list;
		obj* result;

		if (n > static_cast<size_t>(__MAX_BYTES)) {
			return (malloc_alloc::allocate(n));
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if (0 == result) { //û�ж�����ڴ棬�����������
			void *r = refill(ROUND_UP(n));
			return r;
		}
		*my_free_list = result->free_list_link;
		return result;
	}
	//����refill���ڴ������ռ����ʼ��ַ
	//���ֻ���뵽һ������Ĵ�С����ֱ�ӷ���һ���ڴ�Ĵ�С������и�����ڴ棬�ͼ���ִ��
	//�ӵڶ������ڴ濪ʼ���Ѵ��ڴ�����������ڴ�������������������һ�����ڴ�ĵ�ַ���û�
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
	//1.�ڴ�صĴ�С������Ҫ�Ŀռ䣬ֱ�ӷ�����ʼ��ַ��nobjsĬ������Ϊ20������ÿ�ε��ö������������19���ڴ�飩
	//2.�ڴ�ص��ڴ治�������Ϸ�����ô����ڴ棬���ǻ����������һ�������ϵĴ�С���Ǿ�ȫ�������ȥ
	//3.���һ������Ĵ�С���Ѿ��ṩ�����ˣ��Ƚ�������ڴ���һ��С�ڴ�����������棬Ȼ���׼������malloc����40��+��
	//  ���С���ڴ�飨�����ڴ����heap_size���������������ʧ����ת������4���ɹ���ת������6
	//4.������ø�����ڴ�����ͨ���ݹ����������ǵ��ڴ��
	//5.�������û���ڴ�飬ֱ�ӵ���һ���������������ڴ棬����ʧ�ܾ��׳��쳣���ɹ�����ͼ���ִ��
	//6.�����޸��ڴ����ʼ��ַ�ͽ�����ַ��Ϊ��ǰ����ĵ�ַ�飬�ص���chunk_alloc�����ڴ�
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
