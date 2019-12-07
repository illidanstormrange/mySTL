#ifndef __MYSTL_CONSTRUCT_HPP
#define __MYSTL_CONSTRUCT_HPP

#include <new>
#include "myTrait.hpp"
#include "myIterator.hpp"

namespace MySTL{
	template <typename T, typename V>
		inline void construct(T* p, const V& value){
			new(p) T(value);
		}

	template <typename T>
		inline void destroy(T* p){
			p->~T();
		}
	
	template <typename Iterator>
		inline void __destroy_aux(Iterator first, Iterator end, __false_type){
			while(first != end){
				destroy(&*first);
				++first;
			}		
		}
	
	template <typename Iterator>
		inline void __destroy_aux(Iterator first, Iterator end, __true_type){}

	template <typename Iterator, typename T>
		inline void __destroy(Iterator first, Iterator end, T*){
			typedef typename __type_traits<T>::has_trivial_destuctor trivial_destructor;
			__destroy_aux(first, end, trivial_destructor());
		}
	template<typename Iterator>
		inline void destroy(Iterator first, Iterator end){
			__destroy(first, end, value_type(first));
		}
	inline void destroy(char*, char*) {}
	inline void destroy(wchar_t*, wchar_t*) {}
	
}


#endif
