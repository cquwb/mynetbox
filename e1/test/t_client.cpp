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
		send(client_fd, str.c_str(), str.size(), 0);
		int nread = read(client_fd, buf, BUF_SIZE);
		if (nread <= 0)
			break;
		buf[nread] = '\0';
		std::cout << buf << std::endl;
	}

	close(client_fd);

	return 0;
}
