#pragma once
template <typename T>
class Singleton {
public:
	static T& get() {
		static T value{};
		return value;
	}
};