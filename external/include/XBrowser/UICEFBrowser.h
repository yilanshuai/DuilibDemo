#pragma once
#	if defined(XBROWSER_EXPORTS)
#		if	defined(_MSC_VER)
#			define XBROWSER_API __declspec(dllexport)
#		else
#			define XBROWSER_API
#		endif
#	else
#		if defined(_MSC_VER)
#			define XBROWSER_API __declspec(dllimport)
#		else
#			define XBROWSER_API
#		endif
#	endif
#include "include/cef_client.h"
#include "UIlib.h"
#include <include/cef_app.h>
#include <functional>

namespace XBrowser
{
  //缓存清理的类型
  enum ClearDataType {
    CLEAR_DATA_TYPE_NONE = 0x0000,

    CLEAR_ALL_DATA_TYPES = 0x0001,              //all data

    CLEAR_WIPE_PROFILE = 0x0002,                //wipe profile & all data

    CLEAR_DATA_TYPE_SITE_DATA = 0x0004,         //site data

    CLEAR_DATA_TYPE_APP_CACHE = 0x0008,         //appcache

    CLEAR_DATA_TYPE_CACHE = 0x0010,             //cache

    CLEAR_DATA_TYPE_CACHE_STORAGE = 0x0020,     //cacheStorage

    CLEAR_DATA_TYPE_COOKIES = 0x0040,           //cookies

    CLEAR_DATA_TYPE_DOWNLOADS = 0x0080,         //downloads

    CLEAR_DATA_TYPE_FILE_SYSTEMS = 0x0100,      //fileSystems

    CLEAR_DATA_TYPE_FORM_DATA = 0x0200,         //formData

    CLEAR_DATA_TYPE_HISTORY = 0x0400,           //history

    CLEAR_DATA_TYPE_INDEXED_DB = 0x0800,        //indexedDB

    CLEAR_DATA_TYPE_LOCAL_STORAGE = 0x1000,     //localStorage

    CLEAR_DATA_TYPE_PASSWORDS = 0x2000,         //passwords

    CLEAR_DATA_TYPE_CHANNEL_IDS = 0x4000,       //serviceWorkers

    CLEAR_DATA_TYPE_WEB_SQL = 0x8000,           //webSQL
  };

	class CCookieVisitor : public CefCookieVisitor
	{
	private:
		HWND m_hWnd;
		HANDLE m_hEvent;
		bool  m_isRefresh;
		wstring m_url;

	public:
		CCookieVisitor(HANDLE hEvent, HWND hwnd, wstring url, bool isRefrsh = false) :
			m_hEvent(hEvent), m_hWnd(hwnd), m_url(url), m_isRefresh(isRefrsh)
		{
		}
		bool Visit(const CefCookie& cookie, int count, int total, bool& deleteCookie)
		{
			if (count == total)
			{
				return false;
			}
			if (m_hWnd != NULL && cookie.name.str && cookie.value.str)
			{
				wstring strCookie = cookie.name.str;
				strCookie.append(L"=").append(cookie.value.str);
				strCookie.append(L";domain=").append(cookie.domain.str);
				strCookie.append(L";path=").append(cookie.path.str);
				if (cookie.httponly)
					strCookie.append(L";httponly");

				wstring url = m_url;//cookie.domain.str;
				DWORD dwSizeUrl = (wcslen(url.data()) + 1) * 2;
				DWORD dwSizeCookieData = (wcslen(strCookie.data()) + 1) * 2;
				DWORD dwTotalSize = sizeof(DuiLib::CookieData) + dwSizeUrl + dwSizeCookieData;	//要发送的数据总大小

				void* pBuffer = malloc(dwTotalSize);
				memset(pBuffer, 0, dwTotalSize);

				DuiLib::CookieData* pData = static_cast<DuiLib::CookieData*>(pBuffer);
				pData->dwSizeUrl = dwSizeUrl;
				pData->dwSizeCookieName = 0;		//CookieName为空，这个参数在InternetSetCookieExW中一般不用，直接由CookieData提供Cookie名
				pData->dwSizeCookieData = dwSizeCookieData;
				//如果是HttpOnly的Cookie，需要加上该标志
				if (strCookie.find(L"HttpOnly") != -1)
					pData->dwFlags = INTERNET_COOKIE_HTTPONLY;
				else
					pData->dwFlags = NULL;
				pData->dwReserved = NULL;
				//拷贝两个字符串的数据到结构体尾部的柔性数组
				char* pTempChar = pData->pStrData;
				memcpy(pTempChar, url.data(), dwSizeUrl);
				pTempChar += dwSizeUrl;
				memcpy(pTempChar, strCookie.data(), dwSizeCookieData);
				pTempChar = NULL;
				pData = NULL;

				wstring cookies = strCookie;// opc.utf8_encode(cookie);
											//wstring urls = url;// opc.utf8_encode(url);

				COPYDATASTRUCT stCopyData = { 0 };
				stCopyData.cbData = dwTotalSize;
				stCopyData.lpData = pBuffer;
				//通过WM_COPYDATA把数据发给B进程
				::SendMessage(m_hWnd, WM_COPYDATA, 0, reinterpret_cast<LPARAM>(&stCopyData));
				if (!m_isRefresh && count >= total - 1)
				{
					SetEvent(m_hEvent);
				}
			}
			return true;
		}
		//这是一个宏
		//所有的框架类从CefBase继承，实例指针由CefRefPtr管理，CefRefPtr通过调用AddRef()和Release()方法自动管理引用计数。
		IMPLEMENT_REFCOUNTING(CCookieVisitor);
	};

	class BrowserCtrl;

	// CEF的一些delegate接口，需要实现这些接口，代码可以为空
	class BrowserDelegate
	{
	public:
		virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) {}
		virtual void OnBrowserClosing(CefRefPtr<CefBrowser> browser) {}
		virtual void OnBrowserClosed(CefRefPtr<CefBrowser> browser) {}
		virtual void OnBrowserExit(CefRefPtr<CefBrowser> browser) {}
		virtual void OnSetAddress(CefRefPtr<CefBrowser> browser, const wstring& url) {}
		virtual void OnSetTitle(CefRefPtr<CefBrowser> browser, const wstring& title) {}
		virtual void OnSetFullscreen(CefRefPtr<CefBrowser> browser, bool fullscreen) {}
		virtual void OnSetLoadingState(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) {}
		virtual void OnSetDraggableRegions(CefRefPtr<CefBrowser> browser, const vector<CefDraggableRegion>& regions) {}
		virtual void OnNewPage(const wstring& url) {}
		virtual void OnUrlBlocked(const wstring& url) {}
		virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefDownloadItem> download_item,
			const CefString& suggested_name,
			CefRefPtr<CefBeforeDownloadCallback> callback) = 0;
		virtual void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefDownloadItem> download_item,
			CefRefPtr<CefDownloadItemCallback> callback) = 0;
		virtual void OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) {}
		virtual void OnPopupCreated(CefRefPtr<CefBrowser> browser) = 0;
	protected:
		virtual ~BrowserDelegate() {}
	};
	void XBROWSER_API InitCefApp(CefRefPtr<CefApp>& app);
	// 将对应host的请求映射到当前资源的ZIP加密文件中
	// host为服务器域名或IP，如www.baidu.com、192.168.121.137
	// resourceId为资源ID，资源类型必须为ZIPRES
	// password为ZIP文件的解压密码
	void XBROWSER_API InsertResourceMap(wstring host, WORD resourceId, wstring password);
	void XBROWSER_API InsertResourceFileMap(wstring host, wstring resourceFile, wstring password);
  void XBROWSER_API SetResourceFileMapping(string filePath);
  void XBROWSER_API EnableContextMenu(bool state);

	class XBROWSER_API CEFUtil
	{
	public:
		static void SetBeforeNavUrlBlockFilter(function<bool(wstring)> filter);
		static function<bool(wstring)> GetBeforeNavUrlBlockFilter();
		static void SetNewUrlBlockFilter(function<bool(wstring)> filter);
		static function<bool(wstring)> GetNewUrlBlockFilter();
		static void SetInjectV8Extention(function<void()>);
		static function<void()> GetInjectV8Extention();
		static void SetReleaseV8Extention(function<void()>);
		static function<void()> GetReleaseV8Extention();
		static void SetRenderProcessMessageReceived(function<bool(CefRefPtr<CefBrowser>, CefProcessId, CefRefPtr<CefProcessMessage>)>);
		static function<bool(CefRefPtr<CefBrowser>, CefProcessId, CefRefPtr<CefProcessMessage>)> GetRenderProcessMessageReceived();

		static void SetReadBKVideoFileSize(function<size_t()> proc);
		static function<size_t()> GetReadBKVideoFileSize();
		static void SetReadBKVideoFromStart(function<size_t(size_t start, void* ptr, size_t nSize)> proc);
		static function<size_t(size_t start, void* ptr, size_t nSize)> GetReadBKVideoFromStart();

		static void SetReadBKImageFileSize(function<size_t()> proc);
		static function<size_t()> GetReadBKImageFileSize();
		static void SetReadBKImageFromStart(function<size_t(size_t start, void* ptr, size_t nSize)> proc);
		static function<size_t(size_t start, void* ptr, size_t nSize)> GetReadBKImageFromStart();

		static void AddToReplaceUrl(std::pair <wstring, wstring> pair);
		static int GetReplaceCount();
		static std::pair <wstring, wstring> GetReplaceAt(int index);

		static void AddToAllowPlugin(std::wstring plugin);
		static int GetAllowPluginCount();
		static std::wstring GetoAllowPluginAt(int index);

		// 获取策略配置项
		static bool GetCanCopy();
		static bool GetCanSave();
		static bool GetCanDrag();
		static bool GetCanViewSource();
		static bool GetCanPrint();
		static bool GetShowAddressBar();
		static bool GetRecordVisit();

		static void SetCanCopy(bool bTrue);
		static void SetCanSave(bool bTrue);
		static void SetCanDrag(bool bTrue);
		static void SetCanPrint(bool bTrue);
		static void SetCanViewSource(bool bTrue);
		static void SetShowAddressBar(bool bTrue);
		static void SetRecordVisit(bool bTrue);

		static bool GetCanShowDevtools();
		static void SetCanShowDevtools(bool bTrue);

	};

	class XBROWSER_API CCEFBrowserUI : public DuiLib::CControlUI
	{
	public:
		explicit CCEFBrowserUI(HWND hParentWnd, BrowserDelegate* delegate);
		virtual ~CCEFBrowserUI();

		// ------------------以下为继承CControlUI的比较有用的接口 ------------------
		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual void SetPos(RECT rc, bool bNeedInvalidate = true);
		virtual void SetVisible(bool bVisible = true);
		virtual void Invalidate();
		// Returns the browser owned by the window.
		CefRefPtr<CefBrowser> GetBrowser(int nBrowserId) const;

		// ------------------以下为CEF导出接口------------------
		// 新建标签页
		int NewPage(const wstring& url, bool bPopup = false);
		// 显示标签页
		void ShowPage(int nBrowserId);
		//删除标签页
		void DelPage(int nBrowserId);

		// 刷新页面
		void ReLoad(int nBrowserId);
		// 停止页面刷新
		void StopLoad(int nBrowserId);
		// 某个标签页载入url
		void LoadURL(int nBrowserId, const wstring& url);
    //清除缓存
    void ClearCache(int clearType, void(*callback)());

		// 获取该标签页的url
		wstring GetFinalURL(int nBrowserId);

		// 是否能前进|后退及前进后退功能
		BOOL CanGoForward(int nBrowserId);
		void GoForward(int nBrowserId);
		BOOL CanGoBack(int nBrowserId);
		void GoBack(int nBrowserId);

	protected:
		HWND m_hParentWnd;
		int m_nSelectedId;
		BrowserCtrl* m_pCtrl;
		DISALLOW_COPY_AND_ASSIGN(CCEFBrowserUI);
	};
}
