
#include <iostream>
#include "Initializer.h"
#include "ConnectionDispatcher.h"
#include "commands/ConnectionCommand.h"
#include "commands/MessageReadyCommandProcessor.hpp"
void close(Initializer& loader) {
	try {
		loader.close();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "error" << std::endl;
	}
}
int main()
{
	setlocale(LC_ALL, "ru");
	Initializer loader;
	try {
		loader.init();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		close(loader);
		return -1;
	}
	;
	ConnectionDispatcher connectionDispatcher = ConnectionDispatcher(
		loader.getSocket(),
		{ std::shared_ptr<ICommandDispatcher>(new ConnectionCommand()),
		std::shared_ptr<ICommandDispatcher>(new MessageReadyCommandProcessor()) }
	);
	connectionDispatcher.startListen();
	close(loader);
	return 0;
}
