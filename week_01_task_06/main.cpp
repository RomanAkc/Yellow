#include "GetRefStrict.cpp"
#include <iostream>
#include <string>

int main()
{
	std::map<int, std::string> m = { {0, "value"} };
	std::string& item = GetRefStrict(m, 0);
	item = "newvalue";
	std::cout << m[0] << std::endl; // выведет newvalue

	return 0;
}