#ifndef TCPSERVER_H
#define TCPSERVER_H
namespace MyCpp {
	namespace Net {
		class TcpServer {
			public:
				TcpServer(int port) : m_port(port) {
					 IPv4 addr(m_port);
				     Socket sock(AF_INET, SOCK_STREAM, 0); 
				     sock.BindOrDie(addr);
			         sock.ListenOrDie(3);
				}
				Run();

			private:
				int m_port;
				int m_maxConn;
		}
	
	
	
	
	}


}


#endif
