#include <poll.h>
#include <memory>
#include <iostream>
#include "EventHandler.h"

namespace MyCpp {
	namespace Net{
		void PollEventHandler::HandlerEvents(struct pollfd const & pollFd) {
		
			std::cout << "[PoolEventHandler] HandlerEvents, fd:" << pollFd.fd  << " revents:" << pollFd.revents << std::endl;
			if (pollFd.revents & POLLIN) {  
				if (mEventCallBk) {
					mEventCallBk();
				}
			}
		}

		void PollEventHandler::SetRead(bool r) {
			if (r) {
				mFd.events |= POLLIN;
			} else {
				mFd.events &= ~POLLIN;
			}
		}


	}
}


