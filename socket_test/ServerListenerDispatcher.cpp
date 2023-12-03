#include "ServerListenerDispatcher.h"
#include <iostream>
#include <map>
#include "UserInfo.hpp"
#include <vector>
#define DEFAULT_BUFLEN 2048
#define ENTER_USERNAME_MSG "ON_RRPVM_CONNECTION:"
#define MESSAGE_SENT "MESSAGE_SENDING:"
#define MESSAGE_HANDLED "MESSAGE_READY:OK"

static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch) || ch != '\n';
        }));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch) || ch != '\n';
        }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
    rtrim(s);
    ltrim(s);
}


void ServerListenerDispatcher::handleConnections(SOCKET listenSocket)
{
    sockaddr_in clientInfo;

    ZeroMemory(&clientInfo, sizeof(clientInfo));

    int clientInfo_size = sizeof(clientInfo);
	while (!GetAsyncKeyState(VK_RSHIFT)) {
		auto result = accept(listenSocket, (sockaddr*)&clientInfo, &clientInfo_size);
        if (result == INVALID_SOCKET) {
            printf("accept failed: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return;
        }
        else {
            handleConnection(result);
        }
	}
}
std::map<SOCKET, UserInfo> clientMap;
std::vector <std::pair<UserInfo, std::string>> mMessages;

int processInput(SOCKET connSocket, char* recvBuffer, int currLength = 0, int buffLen = DEFAULT_BUFLEN) {
    int iSendResult = 0;
    if (recvBuffer[0] == '\0') {
       iSendResult =  send(connSocket, "ON_RRPVM_CONNECTION:OK", sizeof("ON_RRPVM_CONNECTION:OK"), 0);
    }
    else {
        std::string command = std::string(recvBuffer, currLength / sizeof(char));
        if (strstr(command.c_str(), ENTER_USERNAME_MSG)) {
            std::string username = command.substr(sizeof ENTER_USERNAME_MSG / sizeof(char) -1);
            trim(username);
            clientMap.emplace(connSocket, UserInfo(username));
            iSendResult = send(connSocket, MESSAGE_HANDLED,sizeof MESSAGE_HANDLED, 0);
        }
        else if (strstr(command.c_str(), MESSAGE_SENT)) {
            std::string messagePart = command.substr(sizeof MESSAGE_SENT / sizeof(char) - 1);
            trim(messagePart);
            auto m = clientMap.find(connSocket);
       
            std::cout << "message(" << m->second.mName << "): " << messagePart << std::endl;
            iSendResult = send(connSocket, MESSAGE_HANDLED, sizeof MESSAGE_HANDLED, 0);
        }
        else {
            iSendResult = send(connSocket, "NEXT_COMMAND:OK", sizeof("NEXT_COMMAND:OK"), 0);
        }
    }
   // printf("%s \n", recvBuffer);
    return iSendResult;
}

void ServerListenerDispatcher::handleConnection(SOCKET connSocket)
{
    char recvbuf[DEFAULT_BUFLEN]{};
    int iResult, iSendResult;
    iResult = iSendResult = 0;
    int recvbuflen = DEFAULT_BUFLEN;
    // Receive until the peer shuts down the connection
    do {
        //2 steps:
        //process command() -> send()
        //recv()
        iSendResult = processInput(connSocket, recvbuf, iResult, recvbuflen);
        if (iSendResult == SOCKET_ERROR) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(connSocket);
            return;
        }
        iResult = recv(connSocket, recvbuf, recvbuflen, 0);
    } while (iResult > 0);
}
