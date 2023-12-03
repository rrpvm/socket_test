#pragma once
#include <WinSock2.h>
#include <vector>
#include "ICommandDispatcher.h"
class ConnectionDispatcher
{
public:
	ConnectionDispatcher(SOCKET socket, std::vector<ICommandDispatcher> dispatchers)
		: mSocket(socket), dispatchers(dispatchers) {};
	void startListen();
private:
	ConnectionDispatcher() : mSocket(INVALID_SOCKET) {};
	const SOCKET mSocket;
	std::vector<ICommandDispatcher> dispatchers;
};

