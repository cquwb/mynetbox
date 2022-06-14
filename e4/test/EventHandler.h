#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <poll.h>
#include <functional>
#include <memory>
#include <iostream>

namespace MyCpp {
	namespace Net{
		typedef std::function<void()> EventCallBk;

		class PollLoop;
		typedef std::shared_ptr<PollLoop> PollLoopPtr;

		class PollEventHandler;
		//需要include <memory>
		typedef std::shared_ptr<PollEventHandler> PollEventHandlerPtr;

		class PollEventHandler {
			public:
				//这里应该是一个fd, 针对fd生成一个事件处理对象
				PollEventHandler(int fd);

				/// 这个对象不能走拷贝构造或者赋值操作。只能通过智能指针传递
				/*
				PollEventHandler(const PollEventHandler& p) {
					std::cout << "PoolEventHanler copy construct" << std::endl;
					mFd = p.GetFd();
					mEventCallBk = p.GetEventCallBk();
				}
				*/

				PollEventHandler(const PollEventHandler& ) = delete;
				PollEventHandler operator=(const PollEventHandler& ) = delete;

				void EnableRead(bool en);
				/// 暂时用不到
				void EnableWrite(bool en);

				void DisableAll() { mPollFd.events = 0; }

				/// 提供一个获取原始的
				int GetFd() const {
					return mPollFd.fd;
				}
				///这边需要返回一个引用，减少外面的复制
				struct pollfd const & GetPollFd() const {
					return mPollFd;
				}


				/// 这个对外的函数不需要
				/*
				EventCallBk GetEventCallBk() const {
					return mEventCallBk;
				}
				*/
				void HandlerEvents(struct pollfd const &pollFd);

				void SetReadCallBk(EventCallBk cb) {
					mReadCallBk = std::move(cb);
				}

				/// 注册方法用了友元函数，没有直接用类的成员函数
				friend void ApplyHandlerOnLoop(PollEventHandlerPtr const & h, PollLoopPtr const & loop);
				friend void UnApplyHandlerOnLoop(PollEventHandlerPtr const & h, PollLoopPtr const & loop);

			private:
				/// 这里只有一个mFd其实是够的，但是为了方便在loop里面做unregister.这里可以保存一个loop的index
				struct pollfd mPollFd;
				int mLoopIdx;
				/// 这个成员变量其实没啥用，但是从概念上来说，需要确认自己是属于那个loop的
				// PollLoopPtr mLoop;

				/// 这个才是真正的回调方法，只是这里只是针对读的方法
				EventCallBk mReadCallBk;


		}; ////class最后需要一个分号
	}
}

#endif
