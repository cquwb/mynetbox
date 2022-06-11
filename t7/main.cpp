#include <functional>
#include <iostream>
using namespace std;

void MyFunc1() { cout << "\n\nDelay execute function.\n\n"; }
void MyFunc2(int a, int b) { cout << endl << a + b << endl; }
void MyFunc3(int a, int b, int c, int d) { cout << endl << a + b + c + d << endl; }

int main()
{
	//绑定一个无参函数，建立了一个执行对象
	auto delayFunc1 = std::bind(MyFunc1);
	// 在任何需要的调用执行
	delayFunc1();

	//使用参数占位符，相当于定义了执行对象调用时参数个数
	auto delayFunc2 = std::bind(MyFunc2, std::placeholders::_1, std::placeholders::_2);
	//调用时必须传入两个参数
	delayFunc2(11, 22);

	//在声明时可显示传入参数，并且将需要在调用时传入的参数放置参数占位符，显示传入的参数和参数占位符可以交替书写
	auto delayFunc3 = std::bind(MyFunc3, 11, std::placeholders::_1, 22, std::placeholders::_2);
	delayFunc3(33, 0);  //分别作为参数占位符 std::placeholders::_1 和 std::placeholders::_2

		return 0;
}
