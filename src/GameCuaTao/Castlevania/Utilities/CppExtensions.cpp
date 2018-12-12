#include <algorithm>
#include "CppExtensions.h"

bool Castlevania::ToBoolean(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	auto isstream = std::istringstream{ str };
	auto result = bool{};

	isstream >> std::boolalpha >> result;

	return result;
}

std::vector<std::string> Castlevania::Split(const std::string &str, char delimiter)
{
	auto sstream = std::stringstream{ str };
	auto subStr = std::string{};
	auto results = std::vector<std::string>{};

	while (std::getline(sstream, subStr, delimiter))
	{
		results.push_back(subStr);
	}
	
	return results;
}
