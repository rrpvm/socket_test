#pragma once
#include "../ICommandDispatcher.h"
class MessageReadyCommandProcessor :public ICommandDispatcher
{
public:
    void processCommand(const std::string& fullCommand, const SOCKET socket) override;
    std::string& getCommandName() override;
private:
    std::string mCommandName = "MESSAGE_READY:OK";
};