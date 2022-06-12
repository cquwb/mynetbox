
#include <iostream>
#include "socket.h"
#include "address.h"
#include "acceptor.h"
#include "connect.h"

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		void Acceptor::OnReadMsg() {
			IPv4 addr;
			int conn_fd = mSocket.Accept(&addr);
			std::cout << "get conn fd" << conn_fd << std::endl;
			//这个conn_fd 应该也注册到pool里
			Connect* connectPtr = new Connect(conn_fd, mLoop);
			//为了让connect不销毁
			//mConnects.push_back(connectPtr);

		}
	}
}
