#ifndef _MYTRAIT_
#define _MYTRAIT_

namespace MySTL
{
	struct __true_type {};
	struct __false_type {};
	template <typename T>
		struct __true_traits
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};
	//以下为模板类的偏特化
	template <>
		struct __true_traits<char>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};
	template <>
		struct __true_traits<signed char>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};	
	template <>
		struct __true_traits<unsigned char>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<short>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};
	template <>
		struct __true_traits<unsigned short>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<int>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<unsigned int>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<long>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<unsigned long>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<long long>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<unsigned long long>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<float>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <>
		struct __true_traits<double>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};


	template <>
		struct __true_traits<long double>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

	template <typename T>
		struct __true_traits<T*>
		{
			typedef __false_type has_trivial_default_constructor;
			typedef __false_type has_trivial_copy_constructor;
			typedef __false_type has_trivial_assignment_operator;
			typedef __false_type has_trivial_destructor;
			typedef __false_type is_POD_type;
		};

}

#endif
