#include <iostream>
#include "address.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


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
					m_handlers[j].HandlerEvents(m_fds[j]);
				}

			}

		}

		void PollLoop::RegisterHandler(PollEventHandler const & h) {
			//// const变量这个里面不能调用他的函数 如果要调用 这个函数必须是const
			std::cout << "[Poolloop] Begin RegisterHandler" << std::endl;
			m_fds.push_back(h.GetFd());
			std::cout << "[Poolloop] Begin push" << std::endl;
			m_handlers.push_back(h);
			std::cout << "[Poolloop] end push" << std::endl;
		}

		void PollLoop::UnRegisterHandler(int fd) {
			for(int i = 0; i < m_fds.size();i++) {
				if (m_fds[i].fd == fd) {
					m_fds[i].fd = -1;
					break;
				}
			}
		
		}
	}
}

