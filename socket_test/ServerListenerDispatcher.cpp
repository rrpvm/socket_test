#include "ServerListenerDispatcher.h"
#include <iostream>
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
#define DEFAULT_BUFLEN 512
void ServerListenerDispatcher::handleConnection(SOCKET connSocket)
{
    char recvbuf[DEFAULT_BUFLEN]{};
    int iResult, iSendResult;
    int recvbuflen = DEFAULT_BUFLEN;
    // Receive until the peer shuts down the connection
    do {
        iResult = recv(connSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(connSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed: %d\n", WSAGetLastError());
                closesocket(connSocket);
                return;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(connSocket);
            return;
        }

    } while (iResult > 0);
}
