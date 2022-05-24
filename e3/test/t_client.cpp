#include <sys/socket.h>
#include <string.h>
#include <unistd.h>


#include <iostream>
#include <string>

#include "socket.h"
#include "address.h"


#define BUF_SIZE 1024

int main() {

	Socket sock(AF_INET, SOCK_STREAM, 0);
	if (sock.GetFd() == -1) {
		perror("创建socket失败");
		exit(1);
	}

	IPv4 addr("127.0.0.1", 65530);

	if (-1 == sock.Connect(&addr)) {
		perror("连接失败");
		exit(1);	
	}

	//std::cin 如何从标准输入读取数据
	std::string str;
	char buf[BUF_SIZE];
	while(std::cin >> str) {
		//c_str 是返回一个兼容c的字符数组的对象，返回的其实是首地址的指针
		send(sock.GetFd(), str.c_str(), str.size(), 0);
		int nrecv = recv(sock.GetFd(), buf, BUF_SIZE, 0);
		if (nrecv <= 0)
			break;
		buf[nrecv] = '\0';
		std::cout << buf << std::endl;
	}

	return 0;
}
