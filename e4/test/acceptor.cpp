
#include <iostream>
#include "socket.h"
#include "address.h"
#include "acceptor.h"
#include "connect.h"

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		void Acceptor::OnReadMsg() {
			IPv4Ptr pear_addr = IPv4Ptr(new IPv4);
			int conn_fd = mSocket.Accept(pear_addr);
			std::cout << "get conn fd" << conn_fd << std::endl;
			//这个conn_fd 应该也注册到pool里
			ConnectPtr connectPtr(new Connect(conn_fd, mLoopPtr));
			mConnects.push_back(connectPtr);
			if (mNewConnCallBk) {
				mNewConnCallBk(conn_fd, pear_addr);
			}

		}
	}
}
