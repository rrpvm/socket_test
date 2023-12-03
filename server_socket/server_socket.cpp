
#include <iostream>
#include "Initializer.h"
#include "ConnectionDispatcher.h"
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
	Initializer loader;
	try {
		loader.init();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		close(loader);
		return -1;
	}
	ConnectionDispatcher connectionDispatcher = ConnectionDispatcher(
		loader.getSocket(),
		{}
	);
	connectionDispatcher.startListen();
	close(loader);
	return 0;
}
