#ifndef ADDRESS_H
#define ADDRESS_H

namespace MyCpp {
	namespace Net {
		class IPv4 {
			public:
				IPv4(int port);
				IPv4(const std:String & addr, int port);
				int GetPort();
				const std:String & GetAddr();
			private:
				struct sockaddr_in;
		}
	}
}

#endif
