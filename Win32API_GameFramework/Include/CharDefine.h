#pragma once

#include <iostream>
#include <string>

#ifdef UNICODE
#define tchar			wchar_t
#define tstring			std::wstring
#define to_tstring		std::to_wstring
#else
#define tchar			char
#define tstring			std::string
#define to_tstring		std::to_string
#endif

FORCEINLINE tstring ToTString(std::string str)
{
	tstring tstr;
	tstr.assign(str.begin(), str.end());

	return tstr;
}