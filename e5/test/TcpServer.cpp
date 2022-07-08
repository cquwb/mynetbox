#include <iostream>


class TcpServer {
	public:
		TcpServer(int port):(mPort,port) {
			int fd = socket(AF_INET, SOCK_STREAM, 0);	
			if (fd == -1) {
				perror("open socket error");
			}
			struct sockaddr_in addr;
			addr.Address = 
			bind(fd, (*sockaddr)addr, sizeof(addr));

		
		}


}

int main() {
	int fd = 0;
	struct pollfd pfd(fd, 0, 0);
	pfd.events = POLLIN;

	return 0;
}
