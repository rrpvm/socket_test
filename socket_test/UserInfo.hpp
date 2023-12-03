#include <string>
struct UserInfo {
	UserInfo(std::string name) : mName(name), nameLength(name.length()) {};
	std::string mName;
	const unsigned int nameLength;
};