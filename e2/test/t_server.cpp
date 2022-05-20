#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "address.h"
#include "socket.h"


#include <iostream>


int main() {
	std::cout << "Begin tcp server" << std::endl;

	IPv4 addr(65530, "127.0.0.1");
	Socket sock(AF_INET, SOCK_STREAM, 0);
	if (-1 == sock.Bind(&addr)) {
		perror("socket bind error");
		exit(1);
	}
	if (-1 == sock.Listen(3)) {
		perror("socket listen error");
		exit(1);
	}
	while(1) {
		IPv4 addr;
		int conn_fd = sock.Accept(&addr);
		if (conn_fd == -1) {
			perror("socket accept error");
			exit(1);
		}
		char buf[1024];
		while(1) {
			int nrecv = recv(conn_fd, buf, 1024, 0);
			if (nrecv <= 0) {
				break;
			}
			send(conn_fd, buf, nrecv, 0);
		}
		close(conn_fd);
	}

	return 0;
}
