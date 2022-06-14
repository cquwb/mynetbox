
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include "socket.h"
#include "address.h"
#include "connect.h"

//accept初始化的时候就应该注册事件的处理函数
namespace MyCpp {
	namespace Net {
		void Connect::OnReadMsg() {
			std::cout << "get read msg fd:" << mFd << std::endl;
			char buf[1024];
			int nrecv = recv(mFd, buf, 1024, 0);
			if (nrecv <= 0) {
				std::cout << "close conn_fd = " << mFd << std::endl;
				//如果不主动关闭这个close，poll会一直有这个消息
				close(mFd);
				//这里还需要特殊处理 从pollLoop里把这一行的数据的fd改成-1，不然一直都有事件触发
				mLoopPtr->UnRegisterHandler(mHandler);
			} else {
				send(mFd, buf, nrecv, 0);
			}

		}
	}
}
