#pragma once
#ifndef _Iterator_hpp
#define _Iterator_hpp
#include <stddef.h>

namespace MySTL
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forword_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forword_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	/*定义的空类是为了在调用时，选择不同的重载函数
	 *input_iterator_tag 是输入迭代器：迭代器输入的内容不能更改，只读且只能操作一次
	 *output_iterator_tag 是输出迭代器：只写且只能操作一次
	 *forword_iterator_tag 是正向迭代器：支持读写操作且可以多次操作
	 *bidirectional_iterator_tag 是双向迭代器： 支持双向的操作，且可以多次读写
	 *random_access_iterator_tag 是随即访问迭代器：支持双向移动，且可以多次读写。p+n,p-n等
	 */

	template <class T, class Distence>
	struct input_iterator {
		typedef input_iterator_tag iterator_category;
		typedef T                  value_type;
		typedef Distence           difference_type;
		typedef T*                 pointer;
		typedef T&                 reference;
	};

	struct output_iterator
	{
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;
	};

	template <class T, class Distence>
	struct forword_iterator {
		typedef forword_iterator_tag iterator_category;
		typedef T                  value_type;
		typedef Distence           difference_type;
		typedef T*                 pointer;
		typedef T&                 reference;
	};
	template <class T, class Distence>
	struct bidirectional_iterator {
		typedef bidirectional_iterator_tag iterator_category;
		typedef T                  value_type;
		typedef Distence           difference_type;
		typedef T*                 pointer;
		typedef T&                 reference;
	};
	template <class T, class Distence>
	struct random_access_iterator {
		typedef random_access_iterator_tag iterator_category;
		typedef T                  value_type;
		typedef Distence           difference_type;
		typedef T*                 pointer;
		typedef T&                 reference;
	};


	template <class InputIterator, class Distence>
	inline void __distence(InputIterator first, InputIterator end, Distence &n, input_iterator_tag)
	{
		while (first != end) {
			++first, ++n;
		}
	}


	template <class RandomAccessIterator, class Distence>
	inline void __distence(RandomAccessIterator first, RandomAccessIterator end, Distence &n,
		random_access_iterator_tag)
	{
		n += end - first;
	}


	template <class InputIterator, class Distence>
	inline void distence(InputIterator first, InputIterator end, Distence &n)
	{
		__distence(first, end, n, iterator_category(first));
	}
	//iterator_traits就是 使用typename对参数类型的提取，并对参数类型在进行一次命名
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
	};
	//针对原生指针T* 生成的 traits 偏特化
	template <class T>
	struct iterator_traits<T* >
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T						   value_type;
		typedef ptrdiff_t				   difference_type;
		typedef T *						   pointer;
		typedef T&						   reference;
	};
	//针对原生指针const T*生成的traits偏特化
	template <class T>
	struct iterator_traits<const T* >
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T						   value_type;
		typedef ptrdiff_t				   difference_type;
		typedef T *						   pointer;
		typedef T&						   reference;
	};
	//通过iterator_traits萃取的类型的iterator_category确定迭代器的类型。
	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}
	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type*
		difference_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}
	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}
	template <typename Iterator>
	typename iterator_traits<Iterator>::difference_type
		__distence(Iterator first, Iterator end, struct input_iterator_tag)
	{
		typename iterator_traits<Iterator>::difference_type n = 0;
		while (first != end) {
			++first, ++n;
		}
		return n;
	}

	//trait 编程使用typename和特华、偏特化将迭代器没能支持原生指针，不能推导出函数返回值的问完善了

}
#endif
