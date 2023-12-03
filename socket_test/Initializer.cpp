#include "Initializer.h"
#pragma comment(lib,"Ws2_32.lib")
#include <exception>
#include <WS2tcpip.h>

void Initializer::init()
{
	auto iResult = WSAStartup(MAKEWORD(2, 2), &this->mWsadata);
	if (iResult != 0) {
		throw std::exception("failed to wsa startup" + WSAGetLastError());
	}
	this->mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mSocket == INVALID_SOCKET) {
		closesocket(mSocket);
		throw std::exception("unavailable to create socket" + WSAGetLastError());
	}
	in_addr ip_to_num;
	iResult = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
	if (iResult <= 0) {
		throw std::exception("Error in IP translation to special numeric format" + WSAGetLastError());
	}
	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));
	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(8080);
	iResult = bind(mSocket, (sockaddr*)&servInfo, sizeof(servInfo));
	if (iResult != 0) {
		throw std::exception("Error Socket binding to server info.Error" + WSAGetLastError());
	}
	listenSocket();
}

void Initializer::listenSocket()
{
	auto code = listen(mSocket, SOMAXCONN);
	if (code != 0) {
		throw std::exception("Can't start to listen to. Error # " + WSAGetLastError());
	}
}

void Initializer::close()
{
	auto iResult = closesocket(mSocket);
	if (iResult == SOCKET_ERROR) {
		int error = WSAGetLastError();
		WSACleanup();
		throw std::exception("closesocket failed with error = " + error);
	}
	WSACleanup();
}

SOCKET Initializer::getSocket()
{
	return mSocket;
}
