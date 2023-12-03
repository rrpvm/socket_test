#pragma once
#include "../ICommandDispatcher.h"
class ConnectionCommand :public ICommandDispatcher
{
public:
      void processCommand(const std::string& fullCommand) override;
      std::string& getCommandName() override;
private:
    std::string mCommandName = "ON_RRPVM_CONNECTION";
};