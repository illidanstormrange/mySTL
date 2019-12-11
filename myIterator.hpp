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
	/*����Ŀ�����Ϊ���ڵ���ʱ��ѡ��ͬ�����غ���
	 *input_iterator_tag ���������������������������ݲ��ܸ��ģ�ֻ����ֻ�ܲ���һ��
	 *output_iterator_tag �������������ֻд��ֻ�ܲ���һ��
	 *forword_iterator_tag �������������֧�ֶ�д�����ҿ��Զ�β���
	 *bidirectional_iterator_tag ��˫��������� ֧��˫��Ĳ������ҿ��Զ�ζ�д
	 *random_access_iterator_tag ���漴���ʵ�������֧��˫���ƶ����ҿ��Զ�ζ�д��p+n,p-n��
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
	//iterator_traits���� ʹ��typename�Բ������͵���ȡ�����Բ��������ڽ���һ������
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
	};
	//���ԭ��ָ��T* ���ɵ� traits ƫ�ػ�
	template <class T>
	struct iterator_traits<T* >
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T						   value_type;
		typedef ptrdiff_t				   difference_type;
		typedef T *						   pointer;
		typedef T&						   reference;
	};
	//���ԭ��ָ��const T*���ɵ�traitsƫ�ػ�
	template <class T>
	struct iterator_traits<const T* >
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T						   value_type;
		typedef ptrdiff_t				   difference_type;
		typedef T *						   pointer;
		typedef T&						   reference;
	};
	//ͨ��iterator_traits��ȡ�����͵�iterator_categoryȷ�������������͡�
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

	//trait ���ʹ��typename���ػ���ƫ�ػ���������û��֧��ԭ��ָ�룬�����Ƶ�����������ֵ����������

}
#endif
