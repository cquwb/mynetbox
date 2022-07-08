#ifndef TCPSERVER_H
#define TCPSERVER_H

//服务器类
///*
//1. 开启一个服务器，对外监听端口，接受外面的tcp连接
//
//
//
//
//
class TcpServer {
	private:
		int mPort;
		EventHandler mReadFunc;
		EventLoop mLoop;
	public:
		TcpServer(int port, EventLoop mLoop);
		SetReadFunc(EventHandlerFunc func);

};

class EventLoop {
	public:
		void Register(EventHanddler handler);
		void UnRegister(EventHandler handler);
		void Loop(int timeout); //遍历所有的mFds,判断是有事件发生,需要在一个while环境里调用
					 //如果有事件，在mHandler里面找到对应的EventHandler,调用他的DoHandler方法
	private:
		std::vector<int> mEmptyIds;
		std::vector<struct sockfd> mFds;
		std::vector<EventHandler> mHandler;

};

class EventHandler {
	public:
		//这里实际上只需要传递一个参数fd就行了。不需要传递func
		EventHandler(int fd, EventHandlerFunc func):(mSockFd:pfd,mFunc:func){
			mSockFd.fd = fd;
		}
		void SetReadEvent() {
			mSockFd.events = POLLIN;
		}
		void DoHandler();
		void SetFunc(EvenHandlerFunc func) {mFunc = std::move(func);}
		struct pollfd GetSockFd() {
			return mSockFd;
		}
	private:
		struct pollfd mSockFd;//具体的fd
		EventHandlerFunc mFunc;
};

typedef EventHandlerFunc std::function<void()>


#endif
