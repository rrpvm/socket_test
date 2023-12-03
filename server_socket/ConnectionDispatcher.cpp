#include "ConnectionDispatcher.h"
#include <string>

#define DEFAULT_BUFLEN 512
void ConnectionDispatcher::startListen()
{
	char recvbuf[DEFAULT_BUFLEN]{};
	int recvbuflen = DEFAULT_BUFLEN;
	int bytesReceived = 0;
	do {
		send(mSocket, recvbuf, recvbuflen, 0);

		bytesReceived = recv(mSocket, recvbuf, recvbuflen, 0);
		const std::string mCommand = std::string(recvbuf, bytesReceived);
		auto b = mCommand.c_str();
		for (auto& dispatcher : dispatchers) {
			if (strstr(b, dispatcher.getCommandName().c_str()) == nullptr) continue;

		}
	} while (bytesReceived > 0);
}
