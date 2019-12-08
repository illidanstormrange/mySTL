#ifndef MyVector
#define MyVector
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "myTrait.hpp"
#include "myIterator.hpp"
#include "myConstruct.hpp"

namespace MySTL{
	template<class Type>
		class MyVector{
		public:
			//定义vector自身的嵌套类别
			typedef Type            value_type;
			typedef value_type *    iterator;  
			typedef value_type *    pointer;
			typedef value_type &    reference;
			typedef const value_type * const_iterator;
			typedef const value_type * const_pointer;
			typedef const value_type & const_reference;
		protected:
			//设置空间适配器
			//使用空间的头
			iterator start;
			//使用空间的尾
			iterator end;
			//可使用空间的尾
			iterator end_of_vec;

		public:
			MyVector():start(0), end(0), end_of_vec(0){}
			MyVector(Type value);
			MyVector(MyVector vec);
			MyVector(Type *arr);
			void fill_initalize();
			iterator allocate_and_fill();
		protected:
			
		}
}

#endif
