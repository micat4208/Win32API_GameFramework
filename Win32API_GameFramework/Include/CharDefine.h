#pragma once

#include <iostream>

#ifdef UNICODE
#define tchar wchar_t
#define tstring std::wstring
#else
#define tchar char
#define tstring std::string
#endif

FORCEINLINE tstring ToTString(std::string str)
{
	tstring tstr;
	tstr.assign(str.begin(), str.end());

	return tstr;
}