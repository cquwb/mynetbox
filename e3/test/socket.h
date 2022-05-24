#ifndef SOCKET_H_
#define SOCKET_H_
#include  "address.h"
#include <unistd.h>

class Socket {
	public:
		Socket(int fd) : fd_(fd) {}
		Socket(int domain, int type, int protocol);
		~Socket() {
			if (fd_ > 0) {
				//需要引入#include <unistd.h>
				close(fd_);
			}
		}
		//这个不能为bind会附带掉系统自带的bind函数.
		//函数名可以换得更具体一点, 参数可以换成引用
		//int Bind(IPv4 *addr);
		void BindOrDie(IPv4 const & ip);
		//int Listen(int backlog);
		void ListenOrDie(int backlog);

		//这里按道理也是可以用引用的
		int Accept(IPv4 *addr);
		int GetFd() const {return fd_;}
		int Connect(IPv4 *addr);
	private:
		int fd_;

};
#endif
