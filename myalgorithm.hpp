#ifndef __MY_ALGORITHM_HPP
#define __MY_ALGORITHM_HPP

#include <iostream>
#include <string.h>

#include "myIterator.hpp"
#include "myTrait.hpp"

namespace MySTL
{
	template <typename RandomIterator, typename OutputIterator, typename Distance>
		OutputIterator __copy_d(RandomIterator first, RandomIterator end,
				OutputIterator result, Distance *){
			std::cout << "__copy_d (RandomIterator first, RandomIterator end,OutputIterator result, Distance *" 
					  << std::endl; 
			Distance n = end - first;
			while( n > 0){
				*result = *first;
				++result;
				++first;
				--n;
			}
			return result;
		}
	template<typename T>
		T* __copy_t(const T* first, const T* end, T* result, __false_type){
			std::cout << "__copy_t(const T* first, const T* end, T* result, __false_type)" 
				<< std::endl;
			return __copy_d(first, end, result, (ptrdiff_t*)0);
		}
	template<typename T>
		T* __copy_t(const T* first, const T* end, T* result, __true_type){
			std::cout << "__copy_t(const T* first, const T* end, T* result, __false_type)" 
				<< std::endl;
			memove(result, first, (end - first) * sizeof(T));
			return result + end - first;
		}
	
	template<typename InputIterator, typename OutputIterator>
		OutputIterator __copy(InputIterator first, InputIterator end, OutputIterator result,
				input_iterator_tag){
			std::cout << "__copy(InputIterator first, InputIterator end, OutputIterator result,input_iterator_tag)"
				<< std::endl;
			while(first != end){
				*result = *first;
				++first;
				++result;
			}
			return result;
		}
	template<typename RandomIterator, typename OutputIterator>
		OutputIterator __copy(RandomIterator first, RandomIterator end, OutputIterator result,
				random_access_iterator_tag){
			return __copy_d(first, end, result, difference_type(first));
		}
	template<typename InputIterator, typename OutputIterator>
		struct __copy_dispatch{
			OutputIterator operator()(InputIterator first, InputIterator end, 
					OutputIterator result){
				return __copy(first, end, result, iterator_category(first));
			}	
		};
	template<typename T>
		struct __copy_dispatch<T*, T*>{
			T* operator()(T* first, T* end, T* result){
				typedef typename __true_traits<T>::has_trivial_assignment_operator has_trivial_assignment;
				return __copy_t(first, end, result, has_trivial_assignment());
			}	
		};
	template<typename T>
		struct __copy_dispatch<const T*, T*>
		{	
			T* operator()(const T* first, const T* end, T* result){
				typedef typename __true_traits<T>::has_trivial_assignment_operator has_trivial_assignment;
				return __copy_t(first, end, result, has_trivial_assignment());
			}
		};

	template<typename InputIterator, typename OutputIterator>
		OutputIterator copy(InputIterator first, InputIterator end, OutputIterator result){
			return __copy_dispatch<InputIterator, OutputIterator>()(first, end, result);
		}
	inline	char* copy(const char *first, const char* end, char* result){
		memmove(result, first, (end - first) * sizeof(char));
		return	result + (end - first);
	}
	inline	wchar_t* copy(const wchar_t *first, const wchar_t* end, wchar_t* result){
		memmove(result, first, (end - first) * sizeof(wchar_t));
		return result + (end - first);
	}

	template<typename InputIterator, typename OutputIterator, typename Distance>
		OutputIterator __copy_d_backward(InputIterator first, InputIterator end,
				OutputIterator result, Distance *){
			Distance n = end - first;
			while(n > 0){
				*(result - 1) = *(end - 1);
				--result;
				--end;
				--n;
			}
			return result;
		}
	template<typename InputIterator, typename OutputIterator, typename Distance>
		OutputIterator __copy_t_backward(InputIterator first, InputIterator end,
				OutputIterator result, input_iterator_tag){
			while(end != first){
				*(result - 1) = *(end - 1);
				--result;
				--end;
			}
			return result;
		}
	template<typename InputIterator, typename OutputIterator, typename Distance>
		OutputIterator __copy_t_backward(InputIterator first, InputIterator end,
				OutputIterator result, random_access_iterator_tag){
			return __copy_d_backward(first, end, result, difference_type(first));
		}

	template<typename InputIterator, typename OutputIterator>
		struct __copy_dispatch_backward{
			OutputIterator operator()(InputIterator first, InputIterator end, OutputIterator result){
				return __copy_t_backward(first, end, result, iterator_category(first));
			}
		};
	template<typename T>
		struct __copy_dispatch_backward<T*, T*>{
			T* operator()(T* first, T* end, T* result){
				return __copy_d_backward(first, end, result, (ptrdiff_t*)(0));
			}
		};
	template<typename T>
		struct __copy_dispatch_backward<const T*, T*>{
			T* operator()(const T* first, const T* end, T* result){
				return __copy_d_backward(first, end, result, (ptrdiff_t*)(0));
			}
		};

	template<typename OutputIterator, typename InputIterator>
		OutputIterator copy_backward(InputIterator first, InputIterator end, OutputIterator result){
			return __copy_dispatch_backward<InputIterator, OutputIterator>()(first, end, result);
		}

	template<typename OutputIterator, typename T>
		void fill(OutputIterator first, OutputIterator end, const T& value){
			while(first != end){
				*first = value;
				++first;
			}
		}
	template<typename OutputIterator, typename Size, typename T>
		OutputIterator fill_n(OutputIterator first, Size n, const T& value){
			while(n > 0){
				*first = value;
				--n;
				++first;
			}
			return first;
		}
	template<typename T>
		T max(const T& a, const T& b){
			return a > b ? a : b;
		}

	template<typename InputIterator, typename T>
		InputIterator find(InputIterator first, InputIterator end, const T& value){
			while(first != end && *first != value) ++first;
			return first;
		}

	template<typename T>
		void swap(T& a, T& b){
			T temp = a;
			a = b;
			b = temp;
		}
}
}
#endif
