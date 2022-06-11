#include <iostream>

class X {
	public:
		int& a;
		//这里一定要有声明
		X(int &b);
};

//这里有个冒号
//而且这里必须是初始化列表里在函数里不行
X::X(int& b) : a(b) {
}

/*
 * 这种不行
X::X(int& b) {
	a = b;
}
*/

int main() {
	int i = 2;
	//构造函数不能没有参数
	X x(i);
	return 0;
}
