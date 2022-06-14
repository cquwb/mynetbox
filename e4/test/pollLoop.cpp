#include <iostream>
#include "address.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cassert>

#include "pollLoop.h"
#include "EventHandler.h"


//实现的地方也要加上命名空间
namespace MyCpp {
	namespace Net {
		//实现的地方也要加上返回类型
		void PollLoop::Loop(int timeout) {
			int n = poll(m_fds.data(), m_fds.size(), timeout);			
			if (n > 0) {
				int j;
				for (j = 0; j < m_fds.size(); j++) {
					if (m_fds[j].fd < 0) {
						continue;
					}
					//这边要求传入的不是fd 而是pollfd
					m_handlers[j]->HandlerEvents(m_fds[j]);
				}

			}

		}

		/// 返回值返回最新的index
		int PollLoop::RegisterHandler(PollEventHandlerPtr const & h) {
			//里面没有剩余的空间了
			if (mIdleIdx.empty()) {
				//// const变量这个里面不能调用他的函数 如果要调用 这个函数必须是const
				m_fds.push_back(h->GetPollFd());
				/// 因为改成了不能拷贝，所以这里push 原始指针是不行了
				m_handlers.push_back(h);
				return (m_fds.size()-1);
			} else {
				int idx = mIdleIdx.back();
				mIdleIdx.pop_back();

				m_fds[idx] = h->GetPollFd();
				m_handlers[idx]=h;
				return idx;
			
			}
		}

		void PollLoop::UnRegisterHandler(PollEventHandlerPtr const & h) {
		int idx = h->GetLoopIdx();

		assert(idx >= 0);
		assert(h->GetFd() == m_fds[idx].fd);
		m_fds[idx].fd = -1;
		m_fds[idx].events = 0;
		m_fds[idx].revents = 0;

		/// 减少引用
		m_handlers[idx].reset();

		mIdleIdx.push_back(idx);

		}


		/// 为什么这边是常量，但是可以修改他们的值呢？???
		void ApplyHandlerOnLoop(PollEventHandlerPtr const &h, PollLoopPtr const & p) {
			h->mLoopIdx = p->RegisterHandler(h);
		}
	}
}

