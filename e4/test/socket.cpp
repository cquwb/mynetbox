#include "socket.h"
#include "address.h"
#include <sys/socket.h>
#include <iostream>

Socket::Socket(int domain, int type, int protocol) {
	fd_ = socket(domain, type, protocol);
}

//要inlcude address.h
void Socket::BindOrDie(IPv4 const & ip) {
	//bind #include <sys/socket.h>
	std::cout << ip.GetFamily() << std::endl;
	if (-1 == bind(fd_, ip.GetSockAddr(), sizeof(struct sockaddr_in))) {
		perror("bind error");
		exit(1);
	} 
}

void Socket::ListenOrDie(int backlog) {
	if (-1 == listen(fd_, backlog)) {
		perror("listen error");
		exit(1);
	}
}

int Socket::Accept(IPv4Ptr peer) {
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int fd = accept(fd_, (struct sockaddr *)&addr, &len);
	peer->SetSockAddr(addr);
	if (fd < 0) {
		perror("accept failed");
	}
	return fd;
	//这个地方需要的不是const sockaddr, 是可以修改的
	//return accept(fd_, addr->GetSockAddrPtr(), addr->GetLenAddr());
}


//要inlcude address.h
int Socket::Connect(IPv4 *addr) {
	return connect(fd_, addr->GetSockAddr(), sizeof(struct sockaddr_in));

}

