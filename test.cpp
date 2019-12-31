#include <iostream>
#include "myvector.hpp"
#include "myvector_impl.h"
using namespace MySTL;
int main()
{
	myVector<int> a(10, 1);
	myVector<int> b;
	std::cout << "a = " << a[0] << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "b[0] = " << b[0] << std::endl;
	std::cout << std::endl;
	return 0;
	system("pause");
}
