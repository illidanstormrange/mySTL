#include <iostream>
//#include "myIterator.hpp"
//#include "myConstruct.hpp"
#include "myvector.hpp"
int main(int argc, char * argv[])
{


	MySTL::myVector<int> a(1, 10);
	for(auto a1 : a)
		std::cout << a1 << " ";
	std::cout << "hello world\n" << std::endl;
	return 0;

}
