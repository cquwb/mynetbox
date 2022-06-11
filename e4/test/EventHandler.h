#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <poll.h>
#include <functional>
#include <memory>
#include <iostream>

namespace MyCpp {
	namespace Net{
		typedef std::function<void()> EventCallBk;
		class PollEventHandler;
		//需要include <memory>
		//typedef std::shared_ptr<PollEventHandler> PollEventHandlerPtr;

		class PollEventHandler {
			public:
				//这里应该是一个fd, 针对fd生成一个事件处理对象
				PollEventHandler(int fd) {
					mFd.fd = fd;
					mFd.events = 0;
					mFd.revents = 0;
				}

				PollEventHandler(const PollEventHandler& p) {
					std::cout << "PoolEventHanler copy construct" << std::endl;
					mFd = p.GetFd();
					mEventCallBk = p.GetEventCallBk();
				}

				void SetRead(bool r);

				struct pollfd GetFd() const {
					return mFd;
				}
				EventCallBk GetEventCallBk() const {
					return mEventCallBk;
				}
				void HandlerEvents(struct pollfd const &pollFd);
				void SetEventCallBk(EventCallBk eventCallBk) {
					mEventCallBk = std::move(eventCallBk);
				}

			private:
				struct pollfd mFd;
				EventCallBk mEventCallBk;


		}; ////class最后需要一个分号
	}
}

#endif
