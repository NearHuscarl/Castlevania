#pragma once

#include <sstream>
#include <vector>

namespace Castlevania
{
	// Get value from key in map, if not found, return defaultValue
	// https://stackoverflow.com/a/26958878/9449426
	template<typename MAP>
	const typename MAP::mapped_type &GetValueOrDefault(
		const MAP &map,
		const typename MAP::key_type &key,
		const typename MAP::mapped_type &defaultValue);

	template<typename T, typename E>
	void RemoveByValue(std::vector<T> &list, E removeItem);

	// bool b = ToBoolean("tRuE");
	bool ToBoolean(std::string str);



	template<typename MAP>
	const typename MAP::mapped_type &GetValueOrDefault(
		const MAP &map,
		const typename MAP::key_type &key,
		const typename MAP::mapped_type &defaultValue)
	{
		typename MAP::const_iterator it = map.find(key);
		if (it == map.end())
			return defaultValue;

		return it->second;
	}

	template<typename T, typename E>
	void RemoveByValue(std::vector<T> &list, E removeItem)
	{
		auto it = std::find(list.begin(), list.end(), removeItem);
		
		if (it != list.end())
			list.erase(it);
	}
}