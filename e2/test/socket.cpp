#include "socket.h"
#include "address.h"
#include <sys/socket.h>
#include <iostream>

Socket::Socket(int domain, int type, int protocol) {
	fd_ = socket(domain, type, protocol);
}

//要inlcude address.h
int Socket::Bind(IPv4 *addr) {
	//bind #include <sys/socket.h>
	std::cout << addr->GetFamily() << std::endl;
	return bind(fd_, addr->GetSockAddr(),  addr->GetSocklen()); 
}

int Socket::Listen(int backlog) {
	return listen(fd_, backlog);
}

int Socket::Accept(IPv4 *addr) {
	//这个地方需要的不是const sockaddr, 是可以修改的
	return accept(fd_, addr->GetSockAddrPtr(), addr->GetLenAddr());
}
