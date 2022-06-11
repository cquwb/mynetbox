#ifndef POLLLOOP_H
#define POLLLOOP_H

#include <function>
#include <vector>
#include "EventHandler.h"

namespace MyCpp {
	namespace Net {
		class PollLoop {
			public:
				PollLoop() {
					std:cout << "PollLoop construct" << std::endl;
				}
				//事件触发的函数
				Loop(int timeout);

				RegisterHanlder(PollEventHandlerPtr const &h);
				UnRegisterHandler(PollEventHandlerPtr const &h);
				
			private:
				std::vector<struct pollfd> m_fds;
				std::vector<PollEventHandlerPtr> m_handlers;
					
		}
	}

}
#endif
