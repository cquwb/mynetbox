#ifndef SOCKET_H_
#define SOCKET_H_
#include  "address.h"
#include <unistd.h>

class Socket {
	public:
		Socket(int domain, int type, int protocol);
		~Socket() {
			if (fd_ > 0) {
				//需要引入#include <unistd.h>
				close(fd_);
			}
		}
		//这个不能为bind会附带掉系统自带的bind函数.
		int Bind(IPv4 *addr);
		int Listen(int backlog);
		int Accept(IPv4 *addr);
		int GetFd() {return fd_;}
	private:
		int fd_;

};
#endif
