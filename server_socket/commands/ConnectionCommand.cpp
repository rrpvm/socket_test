#include "ConnectionCommand.h"
#include <iostream>
void ConnectionCommand::processCommand(const std::string& fullCommand)
{
	std::cout << "processCommand(): " << fullCommand << std::endl;

}

std::string& ConnectionCommand::getCommandName()
{
	return this->mCommandName;
}
