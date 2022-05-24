#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class IPv4 {
	public:
		//IPv4();
		//默认构造, 一般用于服务器监听端口
		IPv4(uint16_t port = 0);
		//换成c++string
		IPv4(std::string const & ip, uint16_t port);
		
		//新加的几个函数， 内联函数
		sa_family_t GetFamily() const {return mSockAddr.sin_family;}
		//最后的const代表不会修改任何成员
		std::string GetIp() const;
		uint16_t GetPort() const;
		std::string GetIpPort() const;

		
		//简单的改为内联
		const struct sockaddr * GetSockAddr() const {return (struct sockaddr*)&mSockAddr;}
		//不需要这个
		//struct sockaddr * GetSockAddrPtr();
		//这里是给bind用的需要返回socklen_t, 函数名也换一下
		//// 不需要了
		//socklen_t  GetSocklen();
		//需要引入include<netinet/in.h>
		//socklen_t * GetLenAddr();

		void SetSockAddr(struct sockaddr_in const & addr);
	private:
		//需要引入include<netinet/in.h>
		struct sockaddr_in mSockAddr;
};
#endif

