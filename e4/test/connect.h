#ifndef CONNECT_H
#define CONNECT_H

#include <iostream>
#include <functional>
#include "pollLoop.h"
#include "socket.h"
#include <memory>

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		class Connect {
			public:
				void OnReadMsg();
			public:
				Connect(int fd, PollLoopPtr& p):mFd(fd), mLoopPtr(p) {

					std::cout << "[Connect.h] construct fd " << fd <<std::endl;

					//这里可以不用new 因为在Push的时候发生了拷贝构造
					/////// 因为这里写错了fd, 导致读取到的数据一直是错乱的
					//PollEventHandler ptr(fd);
					PollEventHandlerPtr ptr(new PollEventHandler(mFd)); 
					ptr->EnableRead(true);	
					ptr->SetReadCallBk(std::bind(&Connect::OnReadMsg, this));
					mHandler = ptr;
					ApplyHandlerOnLoop(ptr, p);

				}

				Connect(const Connect&) = delete;
				Connect operator=(const Connect&) = delete;


			private:
				int mFd;
				/// 这里是否一定要用引用？
				/// 不一定要用引用，如果用引用的话，那么在头文件里的connect里必须要能够初始化，因为引用必须立马初始化
				PollEventHandlerPtr mHandler;
				PollLoopPtr & mLoopPtr;

		};

		typedef std::shared_ptr<Connect> ConnectPtr;
	}
}


#endif
