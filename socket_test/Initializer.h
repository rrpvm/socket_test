#pragma once
#include <WinSock2.h>
class Initializer
{
public:
	void init();
	void listenSocket();
	void close();
	SOCKET getSocket();
private:
	WSADATA mWsadata;
	SOCKET mSocket{ INVALID_SOCKET };
};

