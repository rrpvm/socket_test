#pragma once
#include <string>
using SOCKET = unsigned int;
class ICommandDispatcher
{
public:
	virtual void processCommand(const std::string& fullCommand, const SOCKET socket) = 0;
	virtual std::string& getCommandName() = 0;
	~ICommandDispatcher() {}
private:
	
};


