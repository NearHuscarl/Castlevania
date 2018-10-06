#include "WindowUtil.h"

std::wstring WindowUtil::String2WString(const std::string &str)
{
	int strLength = (int)str.length() + 1;
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLength, 0, 0);
	wchar_t* buf = new wchar_t[len];

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLength, buf, len);
	std::wstring wideStr(buf);
	delete[] buf;

	return wideStr;
}