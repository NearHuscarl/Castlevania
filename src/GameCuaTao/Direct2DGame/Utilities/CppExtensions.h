#pragma once

#include <algorithm> 
#include <sstream>
#include <vector>
#include <list>
#include <stack>
#include <cctype>
#include <locale>

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

// https://stackoverflow.com/a/42844629/9449426
bool StartsWith(const std::string &str, const std::string &prefix);
bool EndsWith(const std::string &str, const std::string &suffix);

// https://stackoverflow.com/a/217605/9449426
// trim from start (in place)
static inline void LTrim(std::string &str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch)
	{
		return !std::isspace(ch) && ch != '\n';
	}));
}

// trim from end (in place)
static inline void RTrim(std::string &str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch)
	{
		return !std::isspace(ch) && ch != '\n';
	}).base(), str.end());
}

// trim from both ends (in place)
static inline void Trim(std::string &str)
{
	LTrim(str);
	RTrim(str);
}

// std::vector<std::string> x = Split("one:two::three", ':');
// https://stackoverflow.com/a/236803/9449426
std::vector<std::string> Split(const std::string &str, char delimiter);

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
void RemoveByValue(std::vector<T> &list, E removedItem)
{
	auto it = std::find(list.begin(), list.end(), removedItem);

	if (it != list.end())
		list.erase(it);
}

// http://www.cplusplus.com/reference/list/list/splice/
template<typename T>
typename std::list<T>::iterator Transfer(
	std::list<T> &fromList,
	std::list<T> &toList,
	typename std::list<T>::iterator &it)
{
	auto nextIt = std::next(it);

	// "it" is now invalid.
	toList.splice(toList.end(), fromList, it);

	it = std::prev(toList.end());

	// return next iterator like std::list.erase()
	return nextIt;
}

template<typename T>
T Pop(std::stack<T> &stack)
{
	auto popValue = stack.top();
	stack.pop();

	return popValue;
}
