#pragma once
#include "CharDefine.h"

// �α� ��� ����
#define USE_LOG				true

#ifdef UNICODE
#define CONSOLE_LINKER "/entry:wWinMainCRTStartup /subsystem:console"
#else
#define CONSOLE_LINKER "/entry:WinMainCRTStartup /subsystem:console"
#endif

#if USE_LOG == true
#pragma comment (linker, CONSOLE_LINKER)
#endif

#ifdef UNICODE
#define tcout wcout
#else 
#define tcout cout
#endif

// �α� ��¿� �Լ�
#define LOGF(log) if (USE_LOG) { tcout << TEXT("PATH : ") << __FILE__ << TEXT("[ LINE ") << __LINE__ << TEXT(" ] ") << \
			log << endl; }
#define LOG(log) if(USE_LOG) { tcout << TEXT("[ LINE ") << __LINE__ << TEXT(" ] ") << log << endl; }