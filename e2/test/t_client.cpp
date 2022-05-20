#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


#include <iostream>
#include <string>


#define BUF_SIZE 1024

int main() {

	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == client_fd) {
		perror("创建socket失败");
		exit(1);
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(65530);
	//如果是ipv6的地址，请使用inet_pton方法.
	inet_aton("127.0.0.1", &serv_addr.sin_addr);
	
	//connect 0 success, -1 fail
	if (connect(client_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1 ) {
		perror("连接失败");
		exit(1);	
	}

	//std::cin 如何从标准输入读取数据
	std::string str;
	char buf[BUF_SIZE];
	while(std::cin >> str) {
		//c_str 是返回一个兼容c的字符数组的对象，返回的其实是首地址的指针
		send(client_fd, str.c_str(), str.size(), 0);
		int nrecv = recv(client_fd, buf, BUF_SIZE, 0);
		if (nrecv <= 0)
			break;
		buf[nrecv] = '\0';
		std::cout << buf << std::endl;
	}

	close(client_fd);

	return 0;
}
