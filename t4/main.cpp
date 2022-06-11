#include <iostream>

int main() {
	int x = 3;
	const int& y = x;
	int z = 4;
	x = 5;
	//y = 6; error
	int& a = x;
	//int &b = a; //不可以 不能有引用的引用
	return 0;
}
