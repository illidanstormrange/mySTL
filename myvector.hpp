#pragma once
#ifndef MyVector
#define MyVector
#include "myConstruct.hpp"
#include "myalloc.hpp"
#include "myalgorithm.hpp"
#include "uninitlized.hpp"
#include <iostream>

namespace MySTL {
	template<typename T>
	class myVector
	{
	public:
		//定义vector自身的嵌套类别
		typedef T            value_type;
		typedef value_type *    iterator;
		typedef value_type *    pointer;
		typedef value_type &    reference;
		typedef const value_type * const_iterator;
		typedef const value_type * const_pointer;
		typedef const value_type & const_reference;
		typedef size_t size_type;
	protected:
		iterator allocate_and_fill(size_type n, const T& val) {
			iterator result = date_allocator::allocate(n);
			try{
			uninitlize_fill_n(result, n, val);
			return result;
			}
			catch (...) { date_allocator::deallocate(result, n); }
		}
		void fill_initalize(size_type n, const T& val) {
			start = allocate_and_fill(n, val);
			last = start + n;
			end_of_vec = last;
		}
		void insert_aux(iterator position, const T& value);
		//void insert_aux(iterator position, const T& value);
	protected:
		//设置空间适配器
		typedef simple_alloc<value_type, alloc> date_allocator;
		//使用空间的头
		iterator start;
		//使用空间的尾
		iterator last;
		//可使用空间的尾
		iterator end_of_vec;

	public:
		//iterator
		iterator begin() { return start; }
		iterator end() { return last; }
		//capacity
		size_type size() { return end() - begin(); }
		size_type max_size() { return end_of_vec - begin(); }
		size_type capacity() { return end_of_vec - begin(); }
		bool empty() { return begin() == end(); }
		//element access
		reference operator[](size_type n) { return *(begin() + n); }
		reference front() { return *begin(); }
		reference back() { return *(end() - 1); }
		reference at(size_type n) { return *(begin() + n); }
		//modify
		void push_back(const T& val);
		void pop_back();
		//insert
//		iterator insert (iterator position, const T& val);
//		iterator insert (iterator position, size_type n, const T& val);
		//erase
		iterator erase(iterator position) {
			if (position != end()) {
				copy(position + 1, last, position);
			}
			--this->last;
			destroy(this->last);
			return position;
		}

		iterator erase(iterator first, iterator last) {
			iterator i = copy(last, end(), first);
			destroy(i, end());
			this->last = end() - (last - first);
			return first;
		}

		
		void clear() {
			destroy(begin(), end());
			start = 0;
			this->last = 0;
			end_of_vec = 0;
		}
		void deallocate() {
			if (start) {
				date_allocator::deallocate(start, end_of_vec - start);
			}
		}
		void swap(myVector &x){
			iterator tem_start = start;
			iterator tem_finish = last;
			iterator temp_end_of_vec = end_of_vec;

			start = x.begin();
			last = x.end();
			end_of_vec = x.end_of_vec;

			x.start = tem_start;
			x.last = tem_finish;
			x.end_of_vec = temp_end_of_vec;
		}
		

		void resize(size_type n, const T* val){
			if(n < size()){
				erase(begin() + n, end());
			}
			else{
				insert(end(), n - size(), val);
			}
		}
	public:
		myVector() :start(0), last(0), end_of_vec(0) {}
		myVector(size_type n, const T& val) {fill_initalize(n, val); }
		myVector(int n, const T& val) { fill_initalize(n, val); }
		myVector(long n, const T& val) { fill_initalize(n, val); }
		explicit myVector(size_type n) { fill_initalize(n, value_type()); }
		~myVector() {
			destroy(start, last);
			deallocate();
		}
	};
}

#endif
