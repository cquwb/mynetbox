#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
namespace MyCpp {
	namespace Net{
		class PollEventHandler;
		typedef std::shared_ptr<PollEventHandlerPr> PollEventHandlerPtr;

		class PollEventHandler {
			public:
				void HandlerEvents(struct pollfd const &pollFd);

		}
	}
}

#endif
