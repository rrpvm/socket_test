#pragma once
#include "SIngleton.hpp"
#include <WinSock2.h>
class ServerListenerDispatcher : public Singleton<ServerListenerDispatcher>
{
public:
	void handleConnections(SOCKET s);
	void handleConnection(SOCKET connSocket);
private:
	 
};

