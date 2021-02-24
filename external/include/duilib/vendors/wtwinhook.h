#pragma  once
#include "mhook-lib\mhook.h"
#include <string>
#include <WinInet.h>
#include "proxyutil.h"
#include "operate_config.h"

#define IGNORE_CERT
/****proxy****/
#include <ras.h>
#pragma comment( lib, "rasapi32" )
/****proxy****/
namespace DuiLib {

#define NUMBER_DOCUMENT_MODE 64

#ifdef _M_IX86
#define _M_IX86_X64
#elif defined _M_X64
#define _M_IX86_X64
#endif

#ifndef DEVAPI
#define	DEVAPI	__stdcall		
#endif

#ifdef __cplusplus
	extern "C" {
#endif
		typedef HINTERNET(WINAPI* PFN_InternetOpenW)(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
		typedef HINTERNET(WINAPI* PFN_InternetConnectW)(__in HINTERNET hInternet, __in LPCWSTR lpszServerName, __in INTERNET_PORT nServerPort, __in_opt LPCWSTR lpszUserName, __in_opt LPCWSTR lpszPassword, __in DWORD dwService, __in DWORD dwFlags, __in_opt DWORD_PTR dwContext);
		typedef HINTERNET(WINAPI* PFN_HttpOpenRequestW)(__in HINTERNET hConnect, __in_opt LPCWSTR lpszVerb, __in_opt LPCWSTR lpszObjectName, __in_opt LPCWSTR lpszVersion, __in_opt LPCWSTR lpszReferrer, __in_z_opt LPCWSTR FAR * lplpszAcceptTypes, __in DWORD dwFlags, __in_opt DWORD_PTR dwContext);
		typedef BOOL(WINAPI* PFN_HttpSendRequestW)(HINTERNET hRequest, LPCWSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);
		typedef INTERNET_STATUS_CALLBACK(WINAPI* PFN_InternetSetStatusCallbackA)(HINTERNET hInternet, INTERNET_STATUS_CALLBACK lpfnInternetCallback);
		typedef INTERNET_STATUS_CALLBACK(WINAPI* PFN_InternetSetStatusCallbackW)(HINTERNET hInternet, INTERNET_STATUS_CALLBACK lpfnInternetCallback);
		typedef BOOL(WINAPI* PFN_InternetSetCookieW)(LPCWSTR lpszUrl, LPCWSTR lpszCookieName, LPCWSTR lpszCookieData);
		typedef DWORD(WINAPI* PFN_InternetSetCookieExW)(LPCWSTR lpszUrl, LPCWSTR lpszCookieName, LPCWSTR lpszCookieData, DWORD dwFlags, DWORD_PTR dwReserved);
		// registry query
		typedef LONG(WINAPI *PFN_RegQueryValueExA)(__in HKEY hKey, __in_opt LPCSTR lpValueName, __reserved LPDWORD lpReserved, __out_opt LPDWORD lpType, LPBYTE lpData, __inout_opt LPDWORD lpcbData);
		typedef LONG(WINAPI *PFN_RegQueryValueExW)(_In_ HKEY hKey, _In_opt_ LPCTSTR lpValueName, _Reserved_ LPDWORD lpReserved, _Out_opt_ LPDWORD lpType, _Out_opt_ LPBYTE lpData, _Inout_opt_ LPDWORD lpcbData);
		typedef LONG(WINAPI *PFN_RegOpenKeyExW)(_In_ HKEY hKey, _In_opt_ LPCTSTR lpSubKey, _In_ DWORD ulOptions, _In_ REGSAM samDesired, _Out_ PHKEY phkResult);
		typedef LONG(WINAPI *PFN_RegOpenKeyExA)(_In_ HKEY hKey, _In_opt_ LPCSTR lpSubKey, _In_ DWORD ulOptions, _In_ REGSAM samDesired, _Out_ PHKEY phkResult);
		typedef LONG(WINAPI *PFN_RegCloseKey)(_In_ HKEY hKey);
		typedef LONG(WINAPI *PFN_RegCreateKeyExW)(__in HKEY hKey, __in LPCWSTR lpSubKey, __reserved DWORD Reserved, __in_opt LPWSTR lpClass, __in DWORD dwOptions, __in REGSAM samDesired, __in_opt CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes, __out PHKEY phkResult, __out_opt LPDWORD lpdwDisposition);
		
		typedef BOOL(WINAPI *PFN_InternetReadFile)(_In_ HINTERNET hFile, _Out_ LPVOID lpBuffer, _In_ DWORD dwNumberOfBytesToRead, _Out_ LPDWORD lpdwNumberOfBytesRead);
		typedef BOOL(WINAPI *PFN_InternetQueryDataAvailable)(_In_ HINTERNET hFile, _Out_ LPDWORD lpdwNumberOfBytesAvailable, _In_ DWORD dwFlags, _In_ DWORD_PTR dwContext);

		/*****多进程相关*******/
//该结构体用于从A进程发送InternetSetCookieExW需要的所有参数数据到B进程
		struct CookieData
		{
			DWORD dwSizeUrl;
			DWORD dwSizeCookieName;
			DWORD dwSizeCookieData;		//三个字符串各自的内存占用大小，包含末尾的0x0000，以字节为单位
			DWORD dwFlags;
			DWORD_PTR dwReserved;
			char pStrData[1];			//柔性数组，三个字符串的内容按顺序排列在该字节后
		};
		/***********/

		//
		// reference：
		//   * [HINTERNET](https://msdn.microsoft.com/en-us/library/windows/desktop/aa383766(v=vs.85).aspx)
		// 
		// Flow of HttpSendRequestW:
		// 
		// InternetOpen
		//     |
		//     v
		// InternetConnect
		//     |
		//     v
		// HttpOpenRequest
		//     |
		//     v
		// HttpSendRequest
		//     |
		//     v
		// InternetQueryDataAvailable
		//     |
		//     v
		// InternetReadFile
		//     |
		//     v
		// InternetSetFilePointer
		// 
		class DUILIB_API CWininetHook {

		private:
			CWininetHook(void);
			~CWininetHook(void);

			// helper functions
			static BOOL SetProxy(HINTERNET hInternet, std::wstring url, BOOL enableproxy);
			static BOOL CWininetHook::setPacFile(const LPWSTR proxyAddressStr, const int flags, HINTERNET hInternet);
			static LPTSTR CWininetHook::FindActiveConnection();
			static bool isInject(_In_ HINTERNET hFile);
			static bool isSCA(std::wstring host, wstring port);

		public:

			static void AddToReplaceUrl(std::pair <wstring, wstring> pair);
			static int GetReplaceCount();
			static std::pair <wstring, wstring> GetReplaceAt(int index);

			static void AddToAllowPlugin(std::wstring plugin);
			static int GetAllowPluginCount();
			static std::wstring GetoAllowPluginAt(int index);

			static CWininetHook* GetInstance(HWND hwnd = NULL, DWORD IEVer = 0);

			static BOOL SetIgnoreCert(HINTERNET hRequest);

			// hooked WinINet functions
			static HINTERNET WINAPI  hookedInternetOpenW(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
			static HINTERNET WINAPI  hookedInternetConnectW(__in HINTERNET hInternet, __in LPCWSTR lpszServerName, __in INTERNET_PORT nServerPort, __in_opt LPCWSTR lpszUserName, __in_opt LPCWSTR lpszPassword, __in DWORD dwService, __in DWORD dwFlags, __in_opt DWORD_PTR dwContext);
			static HINTERNET WINAPI  hookedHttpOpenRequestW(__in HINTERNET hConnect, __in_opt LPCWSTR lpszVerb, __in_opt LPCWSTR lpszObjectName, __in_opt LPCWSTR lpszVersion, __in_opt LPCWSTR lpszReferrer, __in_z_opt LPCWSTR FAR * lplpszAcceptTypes, __in DWORD dwFlags, __in_opt DWORD_PTR dwContext);
			static BOOL WINAPI  hookedHttpSendRequestW(HINTERNET hRequest, LPCWSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);
			static INTERNET_STATUS_CALLBACK WINAPI hookedInternetSetStatusCallbackA(HINTERNET hInternet, INTERNET_STATUS_CALLBACK lpfnInternetCallback);
			static INTERNET_STATUS_CALLBACK WINAPI hookedInternetSetStatusCallbackW(HINTERNET hInternet, INTERNET_STATUS_CALLBACK lpfnInternetCallback);
			static BOOL WINAPI hookedInternetSetCookieW(LPCWSTR lpszUrl, LPCWSTR lpszCookieName, LPCWSTR lpszCookieData);
			static DWORD WINAPI hookedInternetSetCookieExW(LPCWSTR lpszUrl, LPCWSTR lpszCookieName, LPCWSTR lpszCookieData, DWORD dwFlags, DWORD_PTR dwReserved);
			static void SyncIECookies(std::wstring url, std::wstring cookie);
			// hooked Registry functions
			static LONG WINAPI hookedRegQueryValueExA(__in HKEY hKey, __in_opt LPCSTR lpValueName, __reserved LPDWORD lpReserved, __out_opt LPDWORD lpType, LPBYTE lpData, __inout_opt LPDWORD lpcbData);
			static BOOL WINAPI hookedRegQueryValueExW(_In_ HKEY hKey, _In_opt_ LPCTSTR lpValueName, _Reserved_ LPDWORD lpReserved, _Out_opt_ LPDWORD lpType, _Out_opt_ LPBYTE lpData, _Inout_opt_ LPDWORD lpcbData);
			static BOOL WINAPI hookedRegOpenKeyExW(_In_ HKEY hKey, _In_opt_ LPCTSTR lpSubKey, _In_ DWORD ulOptions, _In_ REGSAM samDesired, _Out_ PHKEY phkResult);
			static BOOL WINAPI hookedRegOpenKeyExA(_In_ HKEY hKey, _In_opt_ LPCSTR lpSubKey, _In_ DWORD ulOptions, _In_ REGSAM samDesired, _Out_ PHKEY phkResult);
			static BOOL WINAPI hookedRegCloseKey(_In_ HKEY hKey);
			static BOOL WINAPI hookedRegCreateKeyExW(__in HKEY hKey, __in LPCWSTR lpSubKey, __reserved DWORD Reserved, __in_opt LPWSTR lpClass, __in DWORD dwOptions, __in REGSAM samDesired, __in_opt CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes, __out PHKEY phkResult, __out_opt LPDWORD lpdwDisposition);
			static BOOL WINAPI hookedInternetQueryDataAvailable(_In_ HINTERNET hFile, _Out_ LPDWORD lpdwNumberOfBytesAvailable, _In_ DWORD dwFlags, _In_ DWORD_PTR dwContext);
			static BOOL WINAPI hookedInternetReadFile(_In_ HINTERNET hFile, _Out_ LPVOID lpBuffer, _In_ DWORD dwNumberOfBytesToRead, _Out_ LPDWORD lpdwNumberOfBytesRead);

		public:
			// 保存原有被 hook 的方法：
			// WinINet functions
			static PFN_HttpSendRequestW    originHttpSendRequestW;
			static PFN_HttpOpenRequestW    originHttpOpenRequestW;
			static PFN_InternetConnectW      originInternetConnectW;
			static PFN_InternetOpenW         originInternetOpenW;
			static PFN_InternetSetStatusCallbackA originInternetSetStatusCallbackA;
			static PFN_InternetSetStatusCallbackW originInternetSetStatusCallbackW;
			static PFN_InternetSetCookieW     originInternetSetCookieW;
			static PFN_InternetSetCookieExW  originInternetSetCookieExW;
			// Registry functions
			static PFN_RegQueryValueExA originRegQueryValueExA;
			static PFN_RegQueryValueExW originRegQueryValueExW;
			static PFN_RegOpenKeyExW originRegOpenKeyExW;
			static PFN_RegOpenKeyExA originRegOpenKeyExA;
			static PFN_RegCloseKey originRegCloseKey;
			static PFN_RegCreateKeyExW originRegCreateKeyExW;

			static PFN_InternetReadFile  originInternetReadFile;
			static PFN_InternetQueryDataAvailable originInternetQueryDataAvailable;


			static VOID CALLBACK InternetStatusCallback(HINTERNET hInternet, DWORD_PTR dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);

		public:
			// WinINet
			static boolean isCertWarningTry;
			static HANDLE hRequestCompleteEvent;

			static boolean isHookedInternetOpenW;
			static boolean isHookedInternetConnectW;
			static boolean isHookedHttpOpenRequestW;
			static boolean isHookedHttpSendRequestW;
			static boolean isHookedInternetSetStatusCallbackA;
			static boolean isHookedInternetSetStatusCallbackW;
			static boolean isHookedInternetSetCookieW;
			static boolean isHookedInternetSetCookieExW;

			static boolean isHookedInternetReadFile;
			static boolean isHookedInternetQueryDataAvailable;

			static CWininetHook* mWinHook;
			static CRITICAL_SECTION cs;

			static DWORD compatVer;
			static HWND hWnd;//browser process hwnd
			static HWND cWnd;//renderer process hwnd
			static bool syncCookie;//need sync cookie sign
			static bool ignoreCert;//need ignore cert warning sign
		};

#ifdef __cplusplus
	}
#endif
}