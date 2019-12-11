#pragma once
#ifndef __MYALLOC_HPP
#define __MYALLOC_HPP
#include <stdlib.h>

namespace MySTL
{
	//一级配置器
	class __alloc_template
	{
		//以下函数都是在内存不足的时候进行调用的
	private:
		static void *oom_malloc(size_t);  //分配不足
		static void *oom_realloc(void *, size_t); //重新分配不足
		//内存不足设置的处理历程，默认设置为0，表示没有设置处理例程。
		static void(*__malloc_alloc_oom_handler)();
	public:
		static void(*set_malloc_handler(void(*f)()))(){
			void(*old)() = __malloc_alloc_oom_handler;
			__malloc_alloc_oom_handler = f;
			return (old);
		}
		static void * allocate(size_t n) {
			void *result = malloc(n);
			if (0 == result) result = oom_malloc(n);
			return result;
		}
		static void deallocate(void *p, size_t) {
			free(p);
		}
		static void * reallocate(void *p, size_t sz, size_t new_sz) {
			void *result = realloc(p, new_sz);
			if (0 == result) result = oom_realloc(p, new_sz);
			return result;
		}

		//static void free_all();

	};

	// 默认将malloc_alloc设置为0
	typedef __alloc_template malloc_alloc;

	enum { __ALIGN = 8 }; //设置对齐要求，对其为8字节，没有8字节自动补齐
	enum { __MAX_BYTES = 128 }; //第二季配置器的最大一次性申请大小，大于128就调用一级
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };//链表个数，分别代表8， 16， 32...字节的链表





	class alloc
	{
	private:
		union obj {
			union obj *free_list_link;
			char data[1];
		};
	private:
		static obj* free_list[__NFREELISTS];
		static char *start_free;
		static char *end_free;
		static size_t heap_size;
	private:
		static size_t ROUND_UP(size_t bytes) {
			return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));
		}
		//进行对齐操作，将不满8的被树填充成8的倍数
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
		}

		static void *refill(size_t);
		static void *chunk_alloc(size_t, int&);
	public:
		static void *allocate(size_t);
		static void deallocate(void *, size_t);
		static void *reallocate(void *p, size_t, size_t);

	};

	//定义符合STL规格的配置器接口，不管是一级还是二级配置器都使用这个接口进行分配
	template<typename T, typename Alloc>
	class simple_alloc
	{
	public:
		static T* allocate(size_t n) {
			return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
		}
		static T *allocate(void) {
			return (T*)Alloc::allocate(sizeof(T));
		}
		static void deallocate(T *p, size_t n) {
			if (0 != n)
				Alloc::deallocate(p, n * sizeof(T));
		}
		static void deallocate(T *p) {
			Alloc::deallocate(p, sizeof(T));
		}

	};

}

#endif







