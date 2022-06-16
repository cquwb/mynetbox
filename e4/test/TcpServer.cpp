
#include <iostream>
#include <functional>
#include "socket.h"
#include "address.h"
#include "acceptor.h"
#include "connect.h"
#include "TcpServer.h"

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		void TcpServer::OnNewConn(int fd, IPv4Ptr & peer_addr){ 
					std::cout << "[TcpServer] OnNewConn" <<std::endl;
			if (mConnects.size() >= mMaxConn) {
				std::cout << "max connn";
				close(fd);
				return;
			} else {
				ConnectPtr connectPtr(new Connect(fd, mLoopPtr));
				connectPtr->SetRecvRawCallBk(std::bind(mRecvRawCallBk, connectPtr, std::placeholders::_1));
				mConnects.push_back(connectPtr);
				if (mNewConnCallBk) {
					mNewConnCallBk(fd, peer_addr);
				}

			}
		}
	}
}
