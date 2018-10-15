#include "WinHelper.h"

// Copy from
// https://codereview.stackexchange.com/questions/419/converting-between-stdwstring-and-stdstring
std::wstring WinHelper::s2ws(const std::string &str)
{
	int strLength = (int)str.length() + 1;
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLength, 0, 0);
	wchar_t* buf = new wchar_t[len];

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLength, buf, len);
	std::wstring wideStr(buf);
	delete[] buf;

	return wideStr;
}

// https://codereview.stackexchange.com/questions/419/converting-between-stdwstring-and-stdstring
std::string WinHelper::ws2s(const std::wstring &wstr)
{
	int strLength = (int)wstr.length() + 1;
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), strLength, 0, 0, 0, 0);
	char* buf = new char[len];
	
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), strLength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	
	return r;
}