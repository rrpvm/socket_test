#pragma once
#include <string>
class ICommandDispatcher
{
public:
	virtual void processCommand(const std::string& fullCommand) = 0;
	virtual std::string& getCommandName() = 0;
	~ICommandDispatcher() {}
private:
	
};


