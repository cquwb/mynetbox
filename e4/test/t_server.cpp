#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "pollLoop.h"
///// 如果不include出来下面会报 ‘Acceptor’ is not a member of ‘MyCpp::Net’
#include "acceptor.h"

#include <iostream>


int main() {
	//错误的写法
	//MyCpp::Net::PollLoop poll(); //调用的时候要加上命名空间
	MyCpp::Net::PollLoopPtr poll(new MyCpp::Net::PollLoop); //调用的时候要加上命名空间
	MyCpp::Net::Acceptor accept(65530, 3, poll);
	while(1) {
		poll->Loop(2000);
	}
	return 0;
}
