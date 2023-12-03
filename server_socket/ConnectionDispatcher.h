#pragma once
#include <WinSock2.h>
#include <vector>
#include "ICommandDispatcher.h"
#include <memory>
class ConnectionDispatcher
{
public:
	ConnectionDispatcher(SOCKET socket, std::vector<std::shared_ptr<ICommandDispatcher>> dispatchers)
		: mSocket(socket), dispatchers(dispatchers) {};
	void startListen();
	~ConnectionDispatcher() {
		for (auto& v : dispatchers) {
			v.reset();
		}
		dispatchers.clear();
	}
private:
	ConnectionDispatcher() : mSocket(INVALID_SOCKET) {};
	const SOCKET mSocket;
	std::vector<std::shared_ptr<ICommandDispatcher>> dispatchers;
};

