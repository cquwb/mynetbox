#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <iostream>
#include <functional>
#include "pollLoop.h"
#include "socket.h"
#include "connect.h"

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		class Acceptor {
			public:
				Acceptor(int port, int max_conn, PollLoopPtr& p):mSocket(AF_INET, SOCK_STREAM, 0), mLoopPtr(p) {
					IPv4 addr(port);

					mSocket.BindOrDie(addr);
					mSocket.ListenOrDie(max_conn);

				
					//这里可以不用new 因为在Push的时候发生了拷贝构造
					PollEventHandlerPtr ptr(new PollEventHandler(mSocket.GetFd())); 
					///// 这里需要一个取地址的符号
					///// 没有调用这个函数，连接进来的事件也不会触发
					ptr->EnableRead(true);	
					ptr->SetReadCallBk(std::bind(&Acceptor::OnReadMsg, this));
					std::cout << "begin ResigerHandler" << std::endl;
					p->RegisterHandler(ptr);

				}

				void OnReadMsg(); 


			private:
				Socket mSocket;
				PollLoopPtr& mLoopPtr;
				std::vector<Connect> mConnects;

		};
	
	}
}


#endif
