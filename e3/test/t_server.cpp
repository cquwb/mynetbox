#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "address.h"
#include "socket.h"

#include <poll.h>

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
	
	//怎么定义一个数组struct
	int max_conn = 3;
	//错误的写法
	//struct pollfd *fds = struct pollfd[max_conn+1];
	struct pollfd fds[3]; 

	int i;
	for (i = 0; i <= max_conn; i++) {
		fds[i].fd = -1;
	}
	fds[max_conn].fd = sock.GetFd();
	fds[max_conn].events = POLLRDNORM;


	char buf[1024];
	while(1) {
		int n = poll(fds, max_conn+1, 2000);
		std::cout << "poll n " << n << std::endl;
		std::cout << fds  << std::endl;
		std::cout << "events: " << fds[max_conn].revents << std::endl;
		if (n > 0) {
			//先判断有没有accept
			//错误的写法
			//if (fds[max_conn].revents & POLLRDNORM  != 0) {
			// &的优先级 比!= 低
			if ((fds[max_conn].revents & POLLRDNORM ) != 0) {
				for (i = 0; i < max_conn; i++) {
					if (fds[i].fd == -1) {
						break;
					}
				}
				if (i >= max_conn) {
					std::cout << "max connect" << std::endl;
					exit(1);
				}
				IPv4 addr;
				int conn_fd = sock.Accept(&addr);
				fds[i].fd = conn_fd;
				fds[i].events = POLLRDNORM;
			}
			for (i = 0; i < max_conn; i++) {
				if (fds[i].fd == -1) {
					continue;
				}
				if ((fds[i].revents & POLLRDNORM) != 0) {		
					int nrecv = recv(fds[i].fd, buf, 1024, 0);
					if (nrecv <= 0) {
						continue;
					}
					send(fds[i].fd, buf, nrecv, 0);
				}
			}
		}	
	}

	return 0;
}
