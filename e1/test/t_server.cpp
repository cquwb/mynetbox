#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main() {
	std::cout << "Begin tcp server" << std::endl;

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd <= 0) {
		perror("socket error");
		exit(1);
	}
	std::cout <<fd << std::endl;

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(65530);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//ipv4
	//inet_aton("127.0.0.1", &addr.sin_addr);

	if (bind(fd, (struct sockaddr *) &addr,  sizeof(addr)) == -1) {
		perror("bind error");
		exit(1);
	}

	int max_conn = 3;

	if (listen(fd, max_conn) == -1) {
		perror("listen error");
		exit(1);
	}

	while(1) {
		struct sockaddr_in clientAddr;
		socklen_t  addrLen = sizeof(clientAddr);
		int connFd = accept(fd, (struct sockaddr *) &clientAddr, &addrLen);
		if (connFd <= 0) {
			perror("accept error");
			break;
		}
		while (1) {
			char data[1024];
			size_t n = read(connFd, data, 1024);
			if (n <= 0) {
				break;
			}
			send(connFd, data, n, 0);
		}
	}

	return 0;
}
