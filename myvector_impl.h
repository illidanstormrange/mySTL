#ifndef __MYVECTOR_IMPL_H
#define __MYVECTOR_IMPL_H
#include "myvector.hpp"
namespace MySTL
{
	
	template <typename T>
		void myVector<T>::insert_aux(iterator position, const T& value){
			if(last != end_of_vec){
				std::cout << "2" << std::endl;
				construct(last, *(last - 1));
				++last;
				std::cout << "3" << std::endl;
				copy_backward(position, last - 2, last - 1);
				std::cout << "4" << std::endl;
				*position = value;
			}
			else{
				const size_type old_size = size();
				const size_type new_size = (old_size == 0 ? 1 : 2 * old_size);
				iterator new_start = date_allocator::allocate(new_size);
				iterator new_last = uninitlize_copy(start, position, new_last);

				construct(new_last, value);
				++new_last;
				uninitlize_copy(position, last, new_last);

				destroy(begin(), end());
				deallocate();
				start = new_start;
				last = new_last;
				end_of_vec = start + new_size;
			}
		}
	template<typename T>
		void myVector<T>::push_back(const T& val){
			if(last != end_of_vec){
				construct(last, val);
				++last;
			}
			else{
				insert_aux(end(), val);
			}
		}
	template<typename T>
		void myVector<T>::pop_back(){
			--last;
			destroy(last);
		}
}

#endif
