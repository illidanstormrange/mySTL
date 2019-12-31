#pragma once
#include "myIterator.hpp"
#include "myTrait.hpp"
#include "myConstruct.hpp"
#include <string.h>



namespace MySTL
{
	template <class InputIterator, class ForwordIterator>
	inline ForwordIterator __uninitlize_copy_aux(InputIterator first,
		InputIterator end, ForwordIterator result, __true_type) {
		while (first != end) {
			*result = *first;
			++first;
			++result;
		}
		return result;
	}

	template <class InputIterator, class ForwordIterator>
	inline ForwordIterator __uninitlize_copy_aux(InputIterator first,
		InputIterator end, ForwordIterator result, __false_type) {
		while (first != end) {
			std::cout << "first = " << *first << std::endl;
			std::cout << "result = " << &*result << std::endl;
			construct(&*result, *first);
			
			++first;
			++result;
		}
		return result;
	}

	template <class InputIterator, class ForwordIterator, class T>
	inline ForwordIterator __uninitlize_copy(InputIterator first,
		InputIterator end, ForwordIterator result, T*) {
		typedef typename __true_traits<T>::is_POD_type is_POD;
		return __uninitlize_copy_aux(first, end, result, is_POD());
	}


	template <class inputIterator, class ForwordIterator>
	inline ForwordIterator uninitlize_copy(inputIterator first,
		inputIterator end, ForwordIterator result) {
		return __uninitlize_copy(first, end, result, value_type(result));
	}

	inline char* uninitlize_copy(const char* first, const char* end, char* result)
	{
		memmove(result, first, end - first);
		return result + (end - first);
	}

	inline wchar_t* uninitlize_copy(const wchar_t* first, const wchar_t* end, wchar_t* result)
	{
		memmove(result, first, end - first);
		return result + (end - first);
	}
	//从first开始n个元素填充成x值
	template <typename InputIterator, typename T>
	void __uninitlize_fill_aux(InputIterator first, InputIterator end,
		const T& value, __true_type) {
		while (first != end) {
			*first = value;
			++first;
		}
	}

	template <typename InputIterator, typename T>
	void __uninitlize_fill_aux(InputIterator first, InputIterator end,
		const T& value, __false_type) {
		while (first != end) {
			construct(&*first, value);
			++first;
		}
	}

	template <typename InputIterator, typename T, typename U>
	inline void __uninitlize_fill(InputIterator first, InputIterator end,
		const T& value, U*) {
		typedef typename __true_traits<U>::is_POD_type is_POD;
		__uninitlize_fill_aux(first, end, value, is_POD());
	}
	template <typename InputIterator, typename T>
	void uninitlize_fill(InputIterator first, InputIterator end, const T& value) {
		__uninitlize_fill(first, end, value, value_type(first));
	}
	template<typename InputIterator, typename Size, typename T>
	InputIterator __uninitlize_fill_n_aux(InputIterator first, Size n, const T& value,
		__true_type) {
		InputIterator cur = first;
		while (n > 0) {
			*cur = value;
			++cur;
			--n;
		}
		return cur;
	}
	template<typename InputIterator, typename Size, typename T>
	InputIterator __uninitlize_fill_n_aux(InputIterator first, Size n, const T& value,
		__false_type) {
		InputIterator cur = first;
		while (n > 0) {
			construct(&*cur, value);
			++cur;
			--n;
		}
		return cur;
	}

	template<typename InputIterator, typename Size, typename T, typename U>
	InputIterator __uninitlize_fill_n(InputIterator first, Size n, const T& value, U*) {
		typedef typename __true_traits<U>::is_POD_type is_POD;
		return __uninitlize_fill_n_aux(first, n, value, is_POD());
	}

	template <class InputIterator, class Size, class T>
	inline InputIterator uninitlize_fill_n(InputIterator first, Size end,
		const T& x) {
		return __uninitlize_fill_n(first, end, x, value_type(first));
	}


}

