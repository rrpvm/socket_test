#pragma once
#include "../ICommandDispatcher.h"
class ConnectionCommand :public ICommandDispatcher
{
public:
      void processCommand(const std::string& fullCommand,const SOCKET socket) override;
      std::string& getCommandName() override;
private:
    std::string mCommandName = "ON_RRPVM_CONNECTION";
};