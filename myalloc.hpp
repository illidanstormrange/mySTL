#pragma once
#ifndef __MYALLOC_HPP
#define __MYALLOC_HPP
#include <stdlib.h>

namespace MySTL
{
	//һ��������
	class __alloc_template
	{
		//���º����������ڴ治���ʱ����е��õ�
	private:
		static void *oom_malloc(size_t);  //���䲻��
		static void *oom_realloc(void *, size_t); //���·��䲻��
		//�ڴ治�����õĴ������̣�Ĭ������Ϊ0����ʾû�����ô������̡�
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

	// Ĭ�Ͻ�malloc_alloc����Ϊ0
	typedef __alloc_template malloc_alloc;

	enum { __ALIGN = 8 }; //���ö���Ҫ�󣬶���Ϊ8�ֽڣ�û��8�ֽ��Զ�����
	enum { __MAX_BYTES = 128 }; //�ڶ��������������һ���������С������128�͵���һ��
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };//����������ֱ����8�� 16�� 32...�ֽڵ�����





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
		//���ж��������������8�ı�������8�ı���
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

	//�������STL�����������ӿڣ�������һ�����Ƕ�����������ʹ������ӿڽ��з���
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







