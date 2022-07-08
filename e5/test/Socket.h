#ifndef SOCKET_H
#define SOCKET_H

class Socket {
	private:
		int mFd;
	public:
		Socket(int fd);
		Socket(int port);	
};

#endif
