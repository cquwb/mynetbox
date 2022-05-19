#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


#define BUF_SIZE 1024

int main() {
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;
	size_t len;
	ssize_t nread;
	char buf[BUF_SIZE];


	std::cout << "Begin tcp client" << std::endl;
	/* Obtain address(es) matching host/port. */

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* stream socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

	s = getaddrinfo("127.0.0.1", "65530", &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(1);
	}

	/* getaddrinfo() returns a list of address structures.
	 *               Try each address until we successfully connect(2).
	 *                             If socket(2) (or connect(2)) fails, we (close the socket
	 *                                           and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;                  /* Success */

		close(sfd);
	}

	freeaddrinfo(result);           /* No longer needed */

	if (rp == NULL) {               /* No address succeeded */
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}

	//std::cin 如何从标准输入读取数据
	std::string str;
	while(std::cin >> str) {
		send(sfd, str.c_str(), str.size(), 0);
		int nread = read(sfd, buf, 1024);
		if (nread <= 0)
			break;
		//buf[nread] = '\0';
		std::cout << buf << std::endl;
	}

	return 0;
}
