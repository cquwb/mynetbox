#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <sys/socket.h>
#include <netinet/in.h>

class IPv4 {
	public:
		IPv4();
		IPv4(int port, const char * addr);
		const struct sockaddr * GetSockAddr();
		struct sockaddr * GetSockAddrPtr();
		//这里是给bind用的需要返回socklen_t, 函数名也换一下
		socklen_t  GetSocklen();
		//需要引入include<netinet/in.h>
		socklen_t * GetLenAddr();
		short GetFamily() {return addr_.sin_family; }
	private:
		//需要引入include<netinet/in.h>
		struct sockaddr_in addr_;
		socklen_t len_;

};
#endif

