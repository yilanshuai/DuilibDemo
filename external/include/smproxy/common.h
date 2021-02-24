

#ifndef __COMMON_H__

#define __COMMON_H__

// export
#ifdef _WINDOWS
#ifdef DLL_EXPORTS
#define COMMON_API __declspec(dllexport)
#define CALL_CONVENTION __stdcall
#else
#define COMMON_API
#define CALL_CONVENTION __stdcall
#endif
#else
#define COMMON_API 
#define CALL_CONVENTION
#endif

// redefine func and class and route
#define __PASTE(x,y) x##y

#ifndef MIX_PREFIX_UPAPI_CLASS_STR
#define MIX_PREFIX_UPAPI_CLASS_STR "com/wtsecure/safecard/"
#endif

#ifndef MIX_PREFIX_UPAPI_FUNC
#define MIX_PREFIX_UPAPI_FUNC Java_com_wtsecure_safecard_SoftToken_
#endif

#define __MIX_PREFIX_FUNC_PASTE(X,Y) __PASTE(X,Y)
#define __MIX_PREFIX_STR_PASTE(X,Y) X Y

// debug
#ifdef _DEBUG
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__);
#else
#define DEBUG(format,...)
#endif

#define BUFFER_LEN_1K 1024
#define SIZE_1K 1024
#define COUNT_1K 1024
#define MAX_BUFFER_LEN (1024 * 1024)

#define IN
#define OUT

#endif
