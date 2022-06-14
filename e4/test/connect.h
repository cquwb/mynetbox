#ifndef CONNECT_H
#define CONNECT_H

#include <iostream>
#include <functional>
#include "pollLoop.h"
#include "socket.h"

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		class Connect {
			public:
				void OnReadMsg();
			public:
				Connect(int fd, PollLoop& p):mFd(fd), mLoop(p) {

					std::cout << "[Connect.h] construct fd " << fd <<std::endl;

					//这里可以不用new 因为在Push的时候发生了拷贝构造
					/////// 因为这里写错了fd, 导致读取到的数据一直是错乱的
					//PollEventHandler ptr(fd);
					PollEventHandlerPtr ptr(new PollEventHandler(mFd)); 
					ptr->EnableRead(true);	
					ptr->SetReadCallBk(std::bind(&Connect::OnReadMsg, this));
					p.RegisterHandler(ptr);

				}


			private:
				int mFd;
				PollLoop& mLoop;

		};
	}
}


#endif
