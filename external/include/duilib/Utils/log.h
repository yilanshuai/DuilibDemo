#pragma once
//#define NONE_LOG
//#define LOG_FILE
#define LOG_PREFIX_LEN 14
void OutputDebugPrintfA(const char * strOutputString, ...);
void OutputDebugPrintfW(const wchar_t * strOutputString, ...);
#ifdef NONE_LOG
#define LogInfoA
#define LogInfoW
#define LogInfo 
#else
#define LogInfoA OutputDebugPrintfA
#define LogInfoW OutputDebugPrintfW
#ifdef UNICODE
#define LogInfo  LogInfoW
#else
#define LogInfo  LogInfoA
#endif // !UNICODE
#endif // !NONE_LOG

