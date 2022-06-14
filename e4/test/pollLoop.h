#ifndef POLLLOOP_H
#define POLLLOOP_H

#include <vector>
#include <poll.h>
#include <iostream>
#include "EventHandler.h"

namespace MyCpp {
	namespace Net {
		class PollLoop {
			public:
				PollLoop() {
					std::cout << "PollLoop construct" << std::endl;
				}
				//事件触发的函数,监听所有的触发函数
				void Loop(int timeout); //// c++标准普通的函数一定要有返回类型，没有的也是void,否则就会有报错
										//

				void RegisterHandler(PollEventHandlerPtr const &h);
				void UnRegisterHandler(int fd);
				
			private:
				// m_fds相当于是一个触发的事件列表，这些事情是有操作系统触发的。这里只是需要我们
				// 去手动的测试里面哪些触发了。
				std::vector<struct pollfd> m_fds;
				std::vector<PollEventHandlerPtr> m_handlers;
					
		};
	}

}
#endif
