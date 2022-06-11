#include <iostream>


struct Y {
	int b;
};

class X {
	public:
		Y a;
		SetY(Y& y) {a=y;}
};

int Accept(X* pear) {
	struct Y y;
	y.b = 32;
	pear->SetY(y);
	return 1;
}

int main() {
	int i = 2;
	//构造函数不能没有参数
	X x;
	Accept(&x);
	std::cout <<x.a.b << std::endl;
	return 0;
}



