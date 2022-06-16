#include <poll.h>
#include <memory>
#include <iostream>
#include <cassert>
#include "EventHandler.h"

namespace MyCpp {
	namespace Net{
		PollEventHandler::PollEventHandler(int fd):mLoopIdx(-1) {
					mPollFd.fd = fd;
					mPollFd.events = 0;
					mPollFd.revents = 0;
		}
		void PollEventHandler::HandlerEvents(struct pollfd const & pollFd) {
		
			std::cout << "[PoolEventHandler] HandlerEvents, fd:" << pollFd.fd  << " events:" << pollFd.events << " revents:" << pollFd.revents << std::endl;
			std::cout << "PoLLIN:" << POLLIN << ",POLLERRPR"<< POLLERR << ",pollhup" << POLLHUP << ", POLLNVAL" << POLLNVAL << std::endl;
			assert(mPollFd.fd == pollFd.fd);
			assert(mPollFd.events == pollFd.events);
			
			/// 这里为什么要有这么一个赋值？？？
			mPollFd.revents = pollFd.revents;
			if (pollFd.revents & POLLIN) {  
				if (mReadCallBk) {
					mReadCallBk();
				}
			}
		}

		void PollEventHandler::EnableRead(bool en) {
			if (en) {
				mPollFd.events |= POLLIN;
			} else {
				mPollFd.events &= ~POLLIN;
			}
		}


	}
}


