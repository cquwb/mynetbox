#include <iostream>
#include "address.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


IPv4::IPv4(uint16_t port) {
	//struct sockaddr_in addr_ = struct sockaddr_in;
	//一开始的写法错误的，这个写法就是直接初始化了
	//struct sockaddr_in addr_; 
	//#include <string.h>
	memset(&mSockAddr, 0, sizeof(mSockAddr));

	mSockAddr.sin_family = AF_INET;
	mSockAddr.sin_port = htons(port);
	mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}



IPv4::IPv4(std::string const & ip, uint16_t port) {
	//struct sockaddr_in addr_ = struct sockaddr_in;
	//一开始的写法错误的，这个写法就是直接初始化了
	//struct sockaddr_in addr_; 
	//#include <string.h>
	memset(&mSockAddr, 0, sizeof(mSockAddr));

	mSockAddr.sin_family = AF_INET;
	mSockAddr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &mSockAddr.sin_addr) <= 0) {
		std::cout << "地址错误" << std::endl;
		exit(1);
	}
}

std::string IPv4::GetIp() const {
	//TODO 这里为什么可以把函数内的返回出去？
	char buf[64] = "";
	inet_ntop(AF_INET, &mSockAddr.sin_addr, buf, sizeof buf);
	return buf;	
}

uint16_t IPv4::GetPort() const {
	return ntohs(mSockAddr.sin_port);
}

//怎么合并字符串，怎么把整数转化为字符串
std::string IPv4::GetIpPort() const {
	return GetIp() + ":" + std::to_string(GetPort());
}

//这里传引用不会复制一份
void IPv4::SetSockAddr(struct sockaddr_in const &addr) {
	//这里走的是构造函数，会重新复制一份的，所以不会出问题, 那个里面的对象可以被删除掉
	mSockAddr = addr;
}
