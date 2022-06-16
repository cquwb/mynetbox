#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <functional>
#include "pollLoop.h"
#include "socket.h"
#include "connect.h"
#include "acceptor.h"

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		typedef std::function<void(int, IPv4Ptr const &)> NewConnCallBk;
		typedef std::function<void(ConnectPtr const &, RawMsgPtr const &)> RecvRawCallBk;
		typedef std::function<void()> CloseCallBk;

		class TcpServer {
			public:
				TcpServer(int port, int max_conn, PollLoopPtr& p):mLoopPtr(p), mAccept(new Acceptor(port, max_conn)) {
					/// 原来是在函数体里面初始化这个accept 而且也没有赋值给mAccept 导致空间被释放，一直会发POLLNVAL(32)的事件
					/// 这个事件代表文件没有被打开
					//AcceptorPtr accept(new Acceptor(port, max_conn));
					std::cout << "[TcpServer] begin SetNewConn" <<std::endl;
					mAccept->SetNewConn(std::bind(&TcpServer::OnNewConn, this, std::placeholders::_1, std::placeholders::_2));
					std::cout << "[TcpServer] begin register accept handler" <<std::endl;
					p->RegisterHandler(mAccept->GetHandler());
					std::cout << "[TcpServer] end register accept handler" <<std::endl;
				}

				void SetNewConnCallBk(NewConnCallBk cb) {mNewConnCallBk =std::move(cb);}

				void SetRecvRawCallBk(RecvRawCallBk cb) {
					mRecvRawCallBk = std::move(cb);
				}

				void SetCloseCallBk(CloseCallBk cb) {
					mCloseCallBk = std::move(cb);
				}

				void OnNewConn(int fd, IPv4Ptr& peer_addr);


			private:
				AcceptorPtr mAccept;
				PollLoopPtr mLoopPtr;
				std::vector<ConnectPtr> mConnects;
				int mMaxConn;
				/// 添加可自定义的回调函数。方便做自定义的修改
				NewConnCallBk mNewConnCallBk;
				RecvRawCallBk mRecvRawCallBk;
				CloseCallBk mCloseCallBk;

		};
	
	}
}


#endif
