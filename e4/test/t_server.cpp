#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "pollLoop.h"
///// 如果不include出来下面会报 ‘Acceptor’ is not a member of ‘MyCpp::Net’
#include "acceptor.h"
#include "address.h"
#include "connect.h"

#include <iostream>
#include <functional>

using namespace std::placeholders;


void OnNewConnCallBk(int fd, IPv4Ptr peer) {
	std::cout << "OnNewConnCallBk, fd:" << fd << " perer addr:" << peer->GetIpPort() <<std::endl;
}

void OnRecvRawMsg(MyCpp::Net::ConnectPtr const & conn, MyCpp::Net::RawMsgPtr const & msg) {
	std::cout << "OnRecvRawMsgo:" << msg->data() << std::endl;
	conn->SendRawData(msg->data(), msg->size());
}

int main() {
	//错误的写法
	//MyCpp::Net::PollLoop poll(); //调用的时候要加上命名空间
	MyCpp::Net::PollLoopPtr poll(new MyCpp::Net::PollLoop); //调用的时候要加上命名空间
	MyCpp::Net::Acceptor accept(65530, 3, poll);
	accept.SetNewConnCallBk(std::bind(OnNewConnCallBk, _1, _2));
	accept.SetRecvRawCallBk(std::bind(OnRecvRawMsg, _1, _2));
	while(1) {
		poll->Loop(2000);
	}
	return 0;
}
