#include <iostream>
#include "address.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


IPv4::IPv4() {
	//struct sockaddr_in addr_ = struct sockaddr_in;
	//一开始的写法错误的，这个写法就是直接初始化了
	//struct sockaddr_in addr_; 
	//#include <string.h>
	memset(&addr_, 0, sizeof(addr_));
	len_ = sizeof(addr_);
}

IPv4::IPv4(int port, const char * addr) {
	//一开始加了这个会导致下面的操作会编程本地变量的操作
	//c++的构造的初始化是在这个函数执行前就会执行的,所以会在初始化列表里做
	//struct sockaddr_in addr_; 
	memset(&addr_, 0, sizeof(addr_));
	len_ = sizeof(addr_);

	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);
	//ipv4
	//  #include <sys/socket.h>
	//         #include <netinet/in.h>
	//                #include <arpa/inet.h>
	//
	//inet_aton(addr, &addr_.sin_addr);
	inet_pton(AF_INET, addr, &addr_.sin_addr);
}

//这个地方返回的数据，bind方法需要一个const 参数
const struct sockaddr * IPv4::GetSockAddr() {
	return (const struct sockaddr *)&addr_;
}


struct sockaddr * IPv4::GetSockAddrPtr() {
	return (struct sockaddr *)&addr_;
}

socklen_t IPv4::GetSocklen() {
	 return sizeof(addr_);
}

socklen_t * IPv4::GetLenAddr() {
	/*
	 * 这个会编译报错, 把局部变量的地址返回出去了。。
	socklen_t len = sizeof(addr_);
	return &len
	*/
	return &len_;
}
