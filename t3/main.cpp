#include <iostream>

std::string GetStr();
char* GetStr2();

int main() {
	std::string str = GetStr();
	std::cout <<str<<std::endl;


	char *buf = GetStr2();
	std::cout <<buf<<std::endl;
	return 0;
}

std::string GetStr() {
	char buf[64];
	buf[0] = 'h';
	buf[1] = 'e';
	buf[2] = 'l';
	return buf;
}


char* GetStr2() {
	char buf[64];
	buf[0] = 'h';
	buf[1] = 'e';
	buf[2] = 'l';
	return buf;
}
