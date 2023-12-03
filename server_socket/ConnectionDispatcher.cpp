#include "ConnectionDispatcher.h"
#include <string>
#include <thread>
#define DEFAULT_BUFLEN 1024
#define NON_KNOWN_COMMAND "SENT_NOT_KNOWN_COMMAND"
#define IDLE_COMMAND "IDLE"

void ConnectionDispatcher::startListen()
{
	char recvbuf[DEFAULT_BUFLEN]{};
	int recvbuflen = DEFAULT_BUFLEN;
	int bytesReceived = 0;
	do {

		bytesReceived = recv(mSocket, recvbuf, recvbuflen, 0);
		if (bytesReceived <= SOCKET_ERROR) {
			closesocket(mSocket);
			return ;
		}
		const std::string mCommand = std::string(recvbuf, bytesReceived);
		auto mCommandPtr = mCommand.c_str();
		//or nullopt|optional
		const auto& findDispatcher = [this, mCommandPtr]()-> ICommandDispatcher* {
			for (auto& dispatcher : dispatchers) {
				if (strstr(mCommandPtr, dispatcher->getCommandName().c_str()) != nullptr) return dispatcher.get();
			}
			return nullptr;
		};
		ICommandDispatcher* currentDispatcher = findDispatcher();
		if (currentDispatcher != nullptr) {
			currentDispatcher->processCommand(mCommand,mSocket);//send
		}
		else {
			send(mSocket, NON_KNOWN_COMMAND, sizeof NON_KNOWN_COMMAND, 0);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	} while (bytesReceived > 0);
}
