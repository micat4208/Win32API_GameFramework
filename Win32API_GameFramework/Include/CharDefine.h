#pragma once

#include <iostream>

#ifdef UNICODE
#define tchar wchar_t
#define tstring wstring
#else
#define tchar char
#define tstring string
#endif
