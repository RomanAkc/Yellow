#pragma once
#include <string>
#include <map>

enum class Lang {
	DE, FR, IT
};

struct Region {
	std::string std_name;
	std::string parent_std_name;
	std::map<Lang, std::string> names;
	int64_t population;
};