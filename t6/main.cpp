#include <iostream>

int main()
{
	int&&d = 5;
	std::cout << "d的地址是" << &d << std::endl;
	return 0;
} 
