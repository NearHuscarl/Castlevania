#pragma once

#include <sstream>

namespace Castlevania
{
	// Get value from key in map, if not found, return defaultValue
	// https://stackoverflow.com/a/26958878/9449426
	template<typename MAP>
	const typename MAP::mapped_type &GetValueOrDefault(const MAP &map,
		const typename MAP::key_type &key,
		const typename MAP::mapped_type &defaultValue)
	{
		typename MAP::const_iterator it = map.find(key);
		if (it == map.end())
			return defaultValue;

		return it->second;
	}

	// bool b = ToBoolean("tRuE");
	bool ToBoolean(std::string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		auto isstream = std::istringstream{ str };
		auto result = bool{};

		isstream >> std::boolalpha >> result;
		
		return result;
	}
}