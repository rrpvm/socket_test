#include "MessageReadyCommandProcessor.hpp"
#include <iostream>
#include <WinSock2.h>
#define MESSAGE_MAX_LENGTH  1024
#define MESSAGE_SENT "MESSAGE_SENDING:"
void MessageReadyCommandProcessor::processCommand(const std::string& fullCommand, const SOCKET socket)
{
	std::cout << "¬ведите сообщение: ";
	char buffer[MESSAGE_MAX_LENGTH]{ '\0' };
	fgets(buffer, MESSAGE_MAX_LENGTH, stdin);

	const std::string result = MESSAGE_SENT + std::string(buffer, strlen(buffer));
	send(socket, result.c_str(), result.size(), 0);
}

std::string& MessageReadyCommandProcessor::getCommandName()
{
	return this->mCommandName;
}
