#pragma once
#include <windows.h>
#include <tchar.h>
#include "stdafx.h"
#include <sstream>
#include <stdio.h>
#include <list> 

#include <XBrowser/UICEFBrowser.h>
#include <XBrowser/UIMIEBrowser.h>

#include "duilib/UIlib.h"
#include "include/cef_app.h"

using namespace XBrowser;
using namespace DuiLib;

#pragma comment(lib, "cef_sandbox.lib")
#pragma comment(lib, "libcef.lib")
#pragma comment(lib, "libcef_dll_wrapper.lib")
#pragma comment(lib, "DuiLib.lib")
#pragma comment(lib, "XCBrowser.lib")

class CDuiFrameWnd : public WindowImplBase, public XBrowser::BrowserDelegate
{
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual CDuiString GetSkinFile() { return _T("DuiBrow.xml"); }
	virtual CDuiString GetSkinFolder() { return _T(""); }
	virtual void InitWindow()
	{
		m_CEFBrowser = new XBrowser::CCEFBrowserUI(GetHWND(), this);

		CHorizontalLayoutUI* tabstrip1 = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("Tabstrip1")));
		m_CurrentTabStrip = tabstrip1;

		m_ContentView1 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView1")));
		m_ContentView1->Add(m_CEFBrowser);
	}

	virtual void Notify(TNotifyUI& msg)
	{
		CDuiString sCtrlName = msg.pSender->GetName();
		if (msg.sType == _T("click"))
		{
			if (sCtrlName == _T("closebtn"))
			{
				//关闭
				Close();
				return;
			}
			else if (sCtrlName == _T("minbtn"))
			{
				//最小化
				SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
				return;
			}
			else if (sCtrlName == _T("maxbtn"))
			{
				//最大化
				SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
				return;
			}
			else if (sCtrlName == _T("restorebtn"))
			{
				//最大化之后的还原
				SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
				return;
			}
			else if (sCtrlName.Find(_T("tab-option-"), 0) != -1)
			{
				std::wstring ctrlName(sCtrlName.GetData());
				SelectTab(ctrlName.substr(11));
			}
			else if (sCtrlName.Find(_T("tab-close-"), 0) != -1)
			{
				//关闭页签
				std::wstring closeName(sCtrlName.GetData());
				CloseTab(closeName.substr(10));
			}
			else if (sCtrlName == _T("homepageBtn"))
			{
				//查找当前页所在ContentTab和Tabstrip
				CTabLayoutUI* m_ContentTab = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab")));
				CTabLayoutUI* m_ContentTab1 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab1")));
				m_ContentTab->SelectItem(m_ContentTab1);

				CHorizontalLayoutUI* tabstrip1 = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("Tabstrip1")));
				m_CurrentTabStrip = tabstrip1;

				//查找当前页所在ContentView
				CTabLayoutUI* m_ContentView = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("Content")));
				CTabLayoutUI* m_ContentView1 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView1")));
				m_ContentView->SelectItem(m_ContentView1);	

				m_CEFBrowser = new XBrowser::CCEFBrowserUI(GetHWND(), this);
				//m_ContentView1 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView1")));
				m_ContentView1->Add(m_CEFBrowser);
			}
			else if (sCtrlName == _T("personinfoBtn"))
			{
				CTabLayoutUI* m_ContentTab = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab")));
				CTabLayoutUI* m_ContentTab2 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab2")));
				m_ContentTab->SelectItem(m_ContentTab2);

				CHorizontalLayoutUI* tabstrip2 = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("Tabstrip2")));
				m_CurrentTabStrip = tabstrip2;

				CTabLayoutUI* m_ContentView = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("Content")));
				CTabLayoutUI* m_ContentView2 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView2")));
				m_ContentView->SelectItem(m_ContentView2);

				m_CEFBrowser = new XBrowser::CCEFBrowserUI(GetHWND(), this);
				//m_ContentView2 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("m_ContentView2")));
				m_ContentView2->Add(m_CEFBrowser);
				
			}
			else if (sCtrlName == _T("modifypasswordBtn"))
			{
				CTabLayoutUI* m_ContentTab = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab")));
				CTabLayoutUI* m_ContentTab3 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab3")));
				m_ContentTab->SelectItem(m_ContentTab3);

				CHorizontalLayoutUI* tabstrip3 = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("Tabstrip3")));
				m_CurrentTabStrip = tabstrip3;

				CTabLayoutUI* m_ContentView = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("Content")));
				CTabLayoutUI* m_ContentView3 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView3")));
				m_ContentView->SelectItem(m_ContentView3);

				m_CEFBrowser = new XBrowser::CCEFBrowserUI(GetHWND(), this);
				//m_ContentView3 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("m_ContentView3")));
				m_ContentView3->Add(m_CEFBrowser);
			}
			else if (sCtrlName == _T("NewTabButton"))
			{
				UINT tabindex = m_CurrentTabStrip->GetCount();
				CContainerUI* pTab = new CContainerUI;
				CDialogBuilder builder;
				builder.Create(_T("tab.xml"), (UINT)0, NULL, &m_PaintManager, pTab);
				m_CurrentTabStrip->AddAt(pTab, tabindex);

				std::wstring Tid = GetUniqueid();

				COptionUI* option = static_cast<COptionUI*>(m_PaintManager.FindSubControlByClass(pTab, _T("Option"), 0));
				option->SetName((std::wstring(L"tab-option-") + Tid).c_str());
				option->SetGroup(L"group-browser");
				option->SetText(L"新标签页");
				option->SetTextPadding({ 12, 0, 26, 0 });
				option->SetFont(0);

				CButtonUI* close = static_cast<CButtonUI*>(m_PaintManager.FindSubControlByClass(pTab, _T("Button"), 0));

				std::wostringstream closeAttributes;

				
				closeAttributes << L"name=\"tab-close-" << Tid << L"\"";
				close->SetAttributeList(closeAttributes.str().c_str());

				BrowserBundle* bundle = new BrowserBundle(Tid);
				bundle->closeButton = close;
				bundle->TabButton = option;
				bundle->tab = pTab;
				bundle->browserId = m_CEFBrowser->NewPage(L"http://www.baidu.com");
				bundleList.push_back(bundle);
				m_CEFBrowser->ShowPage(bundle->browserId);
			}
		}
	}

	/*****************CEF相关事件********************************************************************/
	void OnBrowserCreated(CefRefPtr<CefBrowser> browser) {}
	void OnBrowserClosing(CefRefPtr<CefBrowser> browser) {}
	void OnBrowserClosed(CefRefPtr<CefBrowser> browser) {}
	void OnBrowserExit(CefRefPtr<CefBrowser> browser) {}
	void OnSetAddress(CefRefPtr<CefBrowser> browser, const wstring& url) {
		//MessageBoxW(NULL, L"OnSetAddress", L"title", MB_OK);
	}
	void OnSetTitle(CefRefPtr<CefBrowser> browser, const wstring& title) {
		int nBrowserId = browser->GetIdentifier();
		for (BrowserBundle* b : bundleList)
		{
			b->TabButton->SetText(title.c_str());
		}
	}
	void OnSetFullscreen(CefRefPtr<CefBrowser> browser, bool fullscreen) {
		//MessageBoxW(NULL, L"OnSetFullscreen", L"title", MB_OK);
	}
	void OnSetLoadingState(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) {
		//MessageBoxW(NULL, L"OnSetLoadingState", L"title", MB_OK);
	}
	void OnSetDraggableRegions(CefRefPtr<CefBrowser> browser, const vector<CefDraggableRegion>& regions) {
		//MessageBoxW(NULL, L"OnSetDraggableRegions", L"title", MB_OK);
	}
	void OnNewPage(const wstring& url) {
		//MessageBoxW(NULL, L"OnNewPage", L"title", MB_OK);
	}
	void OnUrlBlocked(const wstring& url) {
		//MessageBoxW(NULL, L"OnUrlBlocked", L"title", MB_OK);
	}
	void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		const CefString& suggested_name,
		CefRefPtr<CefBeforeDownloadCallback> callback) {
		//MessageBoxW(NULL, L"OnBeforeDownload", L"title", MB_OK);
	};
	void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		CefRefPtr<CefDownloadItemCallback> callback) {
		//MessageBoxW(NULL, L"OnDownloadUpdated", L"title", MB_OK);
	};
	void OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) {
		//MessageBoxW(NULL, L"OnProcessMessageReceived", L"title", MB_OK);
	}
	void OnPopupCreated(CefRefPtr<CefBrowser> browser) {
		//MessageBoxW(NULL, L"OnPopupCreated", L"title", MB_OK);
	};

	std::wstring GetUniqueid()
	{
		wchar_t buf[128] = { 0 };
		GUID guid;
		CoInitialize(NULL);
		if (S_OK == ::CoCreateGuid(&guid))
		{
			swprintf(buf, sizeof(buf),
				L"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
				guid.Data1,
				guid.Data2,
				guid.Data3,
				guid.Data4[0], guid.Data4[1],
				guid.Data4[2], guid.Data4[3],
				guid.Data4[4], guid.Data4[5],
				guid.Data4[6], guid.Data4[7]);
		}
		CoUninitialize();
		return buf;
	}

void SelectTab(std::wstring id)
{
	list<BrowserBundle*>::iterator it;
	for (it = bundleList.begin(); it != bundleList.end(); it++)
	{
		BrowserBundle* bundle = *it;
		if (bundle->id == id)
		{
			m_CEFBrowser->ShowPage(bundle->browserId);
			m_ContentView1->SelectItem(m_CEFBrowser);

		}
	}
}

void CloseTab(std::wstring id)
{
	list<BrowserBundle*>::iterator it;
	for (it = bundleList.begin(); it != bundleList.end(); it++) 
	{
		BrowserBundle* bundle = *it;
		if (bundle->id == id)
		{
			static_cast<CContainerUI*>(bundle->tab->GetParent())->Remove(bundle->tab, true);
			break;
		}
	}
}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//LRESULT lRes = 0;

		//if (uMsg == WM_CREATE)
		//{
		//	m_PaintManager.Init(m_hWnd);
		//	m_PaintManager.AddNotifier(this);   // 添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理
		//	return lRes;
		//}

		//if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		//{
		//	return lRes;
		//}

		return __super::HandleMessage(uMsg, wParam, lParam);

	}

struct BrowserBundle
{
	std::wstring id;
	CContainerUI* tab;
	COptionUI* TabButton;
	CButtonUI* closeButton;
	int browserId;
	BrowserBundle(std::wstring id) : id(id) {}
};

	std::list <BrowserBundle*> bundleList;

private:
	CHorizontalLayoutUI* m_CurrentTabStrip;
	XBrowser::CCEFBrowserUI* m_CEFBrowser;
protected:
	CTabLayoutUI*  m_ContentView1;
};


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	/**/
	// 以下为CEF初始化部分
	// 高清DPI支持
	//CefEnableHighDPISupport();
	void* sandbox_info = NULL;
	// Provide CEF with command-line arguments.
	CefMainArgs main_args(hInstance);
	// Specify CEF global settings here.
	CefSettings settings;
	CefSettingsTraits::init(&settings);
	settings.no_sandbox = true;

	CefRefPtr<CefApp> app;
	XBrowser::InitCefApp(app);
	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
	int exit_code = CefExecuteProcess(main_args, app, sandbox_info);
	if (exit_code >= 0)
	{
		// The sub-process has completed so return here.
		return exit_code;
	}

	CefInitialize(main_args, settings, app.get(), sandbox_info);

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DuilibDemo"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowWindow();

	// 开启CEF的消息循环
	CefRunMessageLoop();
	// DuiLib结束、清理
	DuiLib::CPaintManagerUI::Term();
	// CEF结束、清理
	CefShutdown();

	return 0;
}