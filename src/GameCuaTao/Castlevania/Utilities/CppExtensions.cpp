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
