
#include <iostream>
#include <functional>
#include "socket.h"
#include "address.h"
#include "acceptor.h"
#include "connect.h"

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		void Acceptor::OnReadMsg() {
					std::cout << "[Acceptor] begin onReadMsg" << std::endl;
			IPv4Ptr pear_addr = IPv4Ptr(new IPv4);
			int conn_fd = mSocket.Accept(pear_addr);
			if (mNewConn) {
				mNewConn(conn_fd, pear_addr);
			}
		}
	}
}
