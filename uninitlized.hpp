#include "myIterator.hpp"
#include "myTrait.hpp"
#include <string.h>



namespace MySTL
{

	

	template <class InputIterator, class ForwordIterator>
		inline ForwordIterator __uninitlize_copy_aux(InputIterator first,
				InputIterator end, ForwordIterator result, __true_type){
			while(first != end){
				*result = *first;
				++first;
				++result;
			}
			return result;
		}

	template <class InputIterator, class ForwordIterator>
		inline ForwordIterator __uninitlize_copy_aux(InputIterator first,
				InputIterator end, ForwordIterator result, __false_type){
			while(first != end){
				construct(&*result, *first);
				++first;
				++result;
			}
			return result;
		}

	template <class InputIterator, class ForwordIterator, class T>
		inline ForwordIterator __uninitlize_copy(InputIterator first,
				InputIterator end, ForwordIterator result, T*)
		{
			typedef typename __type_traits<T>::is_POD_type is_POD;
			return __uninitlize_copy_aux(first, end, result, is_POD());
		}


	template <class inputIterator, class ForwordIterator>
		inline ForwordIterator uninitlize_copy(inputIterator first, 
				inputIterator end, ForwordIterator result)
		{
			return __uninitlize_copy(first, end, value_type(result));
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
	
	template <typename InputIterator, typename T>
		void __uninitlize_fill_aux(InputIterator first, InputIterator end,
				const T& value, __true_type){
			while(first != end){
				*first = value;
				++first;
			}
		}

	template <typename InputIterator, typename T>
		void __uninitlize_fill_aux(InputIterator first, InputIterator end,
				const T& value, __false_type){
			while(first != end){
				construct(&*first, value);
				++first;
			}
		}




} 