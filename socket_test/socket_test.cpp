#include <iostream>
#include "Initializer.h"
#include "ServerListenerDispatcher.h"

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
	ServerListenerDispatcher::get().handleConnections(loader.getSocket());
	
	close(loader);
	return 0;
}