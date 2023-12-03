#include "ConnectionCommand.h"
#include <iostream>
#include <WinSock2.h>
#include <fstream>  


void ConnectionCommand::processCommand(const std::string& fullCommand, const SOCKET socket)
{
	std::cout << "processCommand(): " << fullCommand << std::endl;
	std::cout << "enter your username: ";
	char buffer[32]{ '\0' };
	fgets(buffer, 32, stdin);
	int length = 0;
	for (char c : buffer) {
		if (c != '\0' && c != '\n')length++;
	}
	const auto result = this->mCommandName + ":" + std::string(buffer, length);
	send(socket, result.c_str(), result.size(), 0);
}

std::string& ConnectionCommand::getCommandName()
{
	return this->mCommandName;
}
