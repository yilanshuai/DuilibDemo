#pragma once
#include "stdafx.h"
#include <xstring>
#include "../DuiLib/Utils/WinImplBase.h"
//#include <XBrowser/UICEFBrowser.h>
//#include <XBrowser/UIMIEBrowser.h>
//#include "CEFV8HandlerEx.h"

struct BKImageResult;
struct AddAppUIParam;

enum TypeWindowGroup
{
	TYPE_WINDOW_SINGLEGROUP,
	TYPE_WINDOW_MULTIGROUP
};

//enum BROWSER_TYPE
//{
//	//浏览器内核
//	BROWSER_TYPE_MIE,
//	BROWSER_TYPE_CEF,
//	BROWSER_TYPE_CHROME
//};

struct BrowserBundle
{
	//BROWSER_TYPE type;
	std::wstring id;
	int browserid;
	/*COptionUI* tabButton;
	CButtonUI* closeButton;
	CContainerUI* tab;*/
	BrowserBundle(std::wstring id) : id(id) {}
};

struct Application
{
	//map<wstring, shared_ptr<BrowserBundle>> mapping;
	std::wstring link;
};

//------
#define DOWNLOADING_STATE_PAUSE 0
#define DOWNLOADING_STATE_RESUME 1
#define DOWNLOADING_STATE_CANCEL 2
const std::string DownloadStateType[] = { "pause","resume","cancel" };
#define DownloadHtml L"file://wintrust/download.html"
struct Changestate
{
	int Fileid;
	int StateIndex;
};

struct Downloadingstate
{
	int Fileid;
	std::string strstate;
};

struct Downloadedinfor
{
	int nID;
	char filename[100];
	char bytesReceived[30];
	char totalBytes[30];
	bool bIsComplete;
	char state[20];
	char StartTime[25];
	char EndTime[25];
	char SavePath[MAX_PATH];
};
//------

class CBaseWindow : public WindowImplBase, public XBrowser::BrowserDelegate, public XBrowser::MIEDelegate
{
//public:
//	CBaseWindow();
//	virtual LPCTSTR GetWindowClassName() const;
//	virtual CDuiString GetSkinFile();
//	LPCTSTR GetResourceID() const;
//	UILIB_RESOURCETYPE GetResourceType() const;
//	virtual CDuiString GetSkinFolder();
//	virtual void OnFinalMessage(HWND hWnd);
//	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
//	virtual void InitWindow();
//	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	void OnKeyReturn(TNotifyUI& msg);
//
//	shared_ptr<BrowserBundle> AddNewTab(std::wstring url, int appid = -1);
//	shared_ptr<BrowserBundle> AddNewMIETab(std::wstring url, std::string ver, int appid = -1, std::string postBytes = "");
//	shared_ptr<BrowserBundle> AddNewCEFTab(std::wstring url, int appid = -1);
//	shared_ptr<BrowserBundle> MakeBundle(std::wstring id = L"");
//	void CloseTab(std::wstring id);
//	void SelectTab(std::wstring id);
//
//	// dpi相关
//	void setDPI(int DPI);
//	LRESULT OnDPIChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//
//	//------
//	shared_ptr<BrowserBundle> downloadBundle; // 下载管理标签页
//	CDuiString m_HtmlPath;
//	bool m_bIsjsoninit;
//	int kp_isDownloadTabOpen = 0; //下载管理页面是否打开 0没有打开，1代表打开
//								  //int m_nBrowserId_download; // 下载管理id
//	std::string FormatUTC2BJ(CefTime cef_time);
//	std::string FormatINT2STR(int64 ndata);
//	void pushJsonToJS();
//	wstring string2wstring(string str);
//	string wstring2string(wstring wstr);
//	std::vector<Changestate>  m_changestatevector;//记录状态改变的vector
//	std::vector<Downloadingstate>  m_downloadingstate;//记录下载状态的vector
//	std::vector<Downloadedinfor>  m_downloaded_infor;//记录下载完成的信息的vector
//
//													 //------
//													 //增加 2020-01-16 设置地址栏布局状态
//private:
//	void SetAddrVisible(bool bShow);	//bShow  显示：true 隐藏：false
//
//protected:
//	/*****************CEF相关函数********************************************************************/
//	void OnBrowserClosing(CefRefPtr<CefBrowser> browser) OVERRIDE;
//	void OnSetTitle(CefRefPtr<CefBrowser> browser, const std::wstring& title) OVERRIDE;
//	void OnSetAddress(CefRefPtr<CefBrowser> browser, const wstring& url) OVERRIDE;
//	void OnNewPage(const std::wstring& url) OVERRIDE;
//	void OnUrlBlocked(const std::wstring& url) OVERRIDE;
//	void OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) OVERRIDE;
//	void OnPopupCreated(CefRefPtr<CefBrowser> browser) override;
//	void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
//		CefRefPtr<CefDownloadItem> download_item,
//		const CefString& suggested_name,
//		CefRefPtr<CefBeforeDownloadCallback> callback)  override;
//	void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
//		CefRefPtr<CefDownloadItem> download_item,
//		CefRefPtr<CefDownloadItemCallback> callback)  override;
//	/******************MIE delegate函数***************************************************************************/
//	void OnIECreated(int browserid) OVERRIDE;
//	void OnIEClosed(int browserid) OVERRIDE;
//	void OnIEDestroyed(int browserid) OVERRIDE;
//	void OnSetIEURL(int browserid, const std::wstring& url) OVERRIDE;
//	void OnSetIETitle(int browserid, const std::wstring& title) OVERRIDE;
//	void OnUrlBlocked(int browserid, const std::wstring& url) OVERRIDE;
//	void OnNewViewCreated(int browserid) OVERRIDE;
//	void OnNeedCookie(HWND hRenderWnd, wstring url, HANDLE hEvent) OVERRIDE;
//	PFSMProvideUICBSelectClientCert GetSMCertCallback() OVERRIDE;
//	PFSMProvideUICBPinInput GetSMPinCallback() OVERRIDE;
//	virtual void OnClick(TNotifyUI& msg);
//	virtual void OnSelChanged(TNotifyUI& msg);
//	virtual void OnWindowInited(TNotifyUI& msg);
//
//	/*****************COOKIE相关*******************************************/
//	LRESULT OnSetCookieData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	DUI_DECLARE_MESSAGE_MAP()
//
//
//protected:
//	unordered_map<wstring, shared_ptr<BrowserBundle>> m_hashAll;
//	unordered_map<int, shared_ptr<BrowserBundle>> m_hashMIE;
//	unordered_map<int, shared_ptr<BrowserBundle>> m_hashCEF;
//	unordered_map<int, shared_ptr<BrowserBundle>> m_hashBookmark;
//	shared_ptr<BrowserBundle> m_currentBundle;
//	XBrowser::CCEFBrowserUI* m_CEFBrowser;
//	XBrowser::CMIEBrowserUI* m_MIEBrowser;
//	CTabLayoutUI* m_ContentView;
//	CContainerUI* m_pContentView;
//	CTabLayoutUI* m_pContent;
//	CEditUI* m_pAddressUI;
//	bool m_bCloseCEF;
//
//	//CWndShadow m_WndShadow;
};
