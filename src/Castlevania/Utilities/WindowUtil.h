#pragma once

#include <string>
#include <windows.h>

class WindowUtil
{
public:
	static std::wstring String2WString(const std::string &str);
};