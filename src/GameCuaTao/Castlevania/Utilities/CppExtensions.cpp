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

bool Castlevania::StartsWith(std::string str, std::string subStr)
{
	return str.compare(0, subStr.length(), subStr) == 0;
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
