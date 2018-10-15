#include "WinHelper.h"

// Copy from
// https://codereview.stackexchange.com/questions/419/converting-between-stdwstring-and-stdstring
std::wstring WinHelper::s2ws(const std::string &str)
{
	auto strLength = (int)str.length() + 1;
	auto len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLength, 0, 0);
	auto buf = new wchar_t[len];

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLength, buf, len);
	auto wideStr = std::wstring{ buf };
	delete[] buf;

	return wideStr;
}

// https://codereview.stackexchange.com/questions/419/converting-between-stdwstring-and-stdstring
std::string WinHelper::ws2s(const std::wstring &wstr)
{
	auto strLength = (int)wstr.length() + 1;
	auto len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), strLength, 0, 0, 0, 0);
	auto buf = new char[len];
	
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), strLength, buf, len, 0, 0);
	auto r = std::string{ buf };
	delete[] buf;
	
	return r;
}