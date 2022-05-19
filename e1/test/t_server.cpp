#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


#include <iostream>


int main() {
	std::cout << "Begin tcp server" << std::endl;

	//打开一个socket tcp的fd
	/*
	 *  #include <sys/socket.h>
	 * int socket(int domain, int type, int protocol);
	 * return -1 就表示出错。其他情况是一个文件描述符
	 * 
	 */
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd == 1) {
		perror("socket error");
		exit(1);
	}
	std::cout << listen_fd << std::endl;

	/*
	 * #include<netinet/in.h>
	 * sockaddr_in 是internet环境下套接字的地址形式
	 struct sockaddr_in {
	 	short   sin_family;         //address family
	 	u_short sin_port;           //16 bit TCP/UDP port number
	 	struct  in_addr sin_addr;   //32 bit IP address
	 	char    sin_zero[8];        //not use, for align
	 };
	 这个是可以和sockaddr 互相强制转换的
	 https://blog.csdn.net/ZWE7616175/article/details/80252048
	 */
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(65530);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//ipv4
	//inet_aton("127.0.0.1", &addr.sin_addr);

	//bind 成功返回0，失败返回-1
	if (bind(listen_fd, (struct sockaddr *) &serv_addr,  sizeof(serv_addr)) == -1) {
		perror("bind error");
		exit(1);
	}

	int max_conn = 10;

	//listen 成功返回0，失败返回-1
	//第二个代表等待队列的长度
	if (listen(listen_fd, max_conn) == -1) {
		perror("listen error");
		exit(1);
	}

	while(1) {
		struct sockaddr_in cli_addr;
		socklen_t len = sizeof(cli_addr);
		//成功返回一个非负的整数，代表文件描述符(0 也是正确的)，失败返回-1
		int conn_fd = accept(listen_fd, (struct sockaddr *) &cli_addr, &len);
		if (conn_fd == -1) {
			perror("accept error");
			exit(1);
		}
		//放到外面
		char buf[1024];
		while (1) {
			int nread = read(conn_fd, buf, 1024);
			if (nread <= 0) {
				break;
			}
			send(conn_fd, buf, nread, 0);
		}
		//不要忘了close
		close(conn_fd);
	}
	//不要往了close
	close(listen_fd);

	return 0;
}
