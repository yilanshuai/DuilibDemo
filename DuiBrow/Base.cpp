#include "stdafx.h"
#include "Base.h"

//#include <XBrowser/UICEFBrowser.h>
//#include <XBrowser//UIMIEBrowser.h>
#include "../DuiLib/Utils/Utils.h"
#include "../DuiLib/Core/UIDefine.h"
//#include "define.h"
//#include <json/value.h>
//#include <json/reader.h>
#include <fstream>
//#include "BookmarkWindow.h"
//#include "BookmarkMgrWindow.h"
//#include "InstallVersion.h"
//#include "RemoteInfo.h"
//------
#include <Shlobj.h>
#include "resource.h"
//#include "TipMsgWnd.h"
#include <stdio.h>
#include <shellapi.h>
//------
#pragma warning(disable: 4100)

typedef struct _tag_HOOKDATA
{
	int nType;
	HOOKPROC hkProc;
	HHOOK hHook;
} TAG_HOOK_DATA;

/// Hook键盘产生的数据,Ctrl+W时，发送消息给窗口，关闭当前标签页

TAG_HOOK_DATA g_KbHookData;
HWND g_hHwndMain = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//if (0 == nCode)
	//{
	//	switch (wParam)
	//	{
	//		// 'W' 键盘的16进制ASCII码
	//	case 0x57:
	//	{
	//		// 判断按键状态
	//		// 参考 https://docs.microsoft.com/zh-cn/previous-versions/windows/desktop/legacy/ms644984(v=vs.85)
	//		if ((HIWORD(lParam) & 0xC000) == 0)
	//		{
	//			// 窗口有效
	//			if (NULL != g_hHwndMain)
	//			{
	//				// Ctrl键已经按下
	//				if (GetKeyState(VK_CONTROL) < 0)
	//				{
	//					PostMessage(g_hHwndMain, WM_DEL_CURRENT_TAB, 0, 0);
	//				}

	//			}
	//		}
	//	}
	//	break;

		//add by yilanshuai for 快捷键CTRL+D 进行收藏
		//'D'键盘的16进制ASCII码
		//case 0x44:
		//{
		//	if ((HIWORD(lParam) & 0xC000) == 0)
		//	{
		//		if (NULL != g_hHwndMain)
		//		{
		//			if (GetKeyState(VK_CONTROL) < 0)
		//			{
		//				//当前窗口的句柄
		//				auto bw = BookmarkMgrWindow::GetInstance(g_hHwndMain);
		//				bw->SetName(L"");
		//				bw->SetUrl(L"");
		//				bw->CenterWindow();
		//				bw->ShowWindow(true, true);
		//			}
		//		}		
		//	}
		//}
		//break;

		//add by yilanshuai for 快捷键ALT+N 新建标签页
		//'N'键盘的16进制ASCII码
		/*case 0x4E:
		{
		if ((HIWORD(lParam) & 0xC000) == 0)
		{
		if (NULL != g_hHwndMain)
		{
		if (GetKeyState(VK_MENU) < 0)
		{
		auto bw = BookmarkMgrWindow::GetInstance(g_hHwndMain);

		}
		}
		}
		}
		break;*/

		/*default:
			break;
		}
	}
	return CallNextHookEx(g_KbHookData.hHook, nCode, wParam, lParam);*/
}


// 上海电信无纸化测试添加，弹出窗口信息保存，在弹出窗口关闭以后将消息传送给CEF进程
//namespace
//{
//	typedef std::pair<int, CefRefPtr<CefBrowser>> PopCloseInfo;
//	std::unordered_map<int, PopCloseInfo> PopCloseStore;
//}

DUI_BEGIN_MESSAGE_MAP(CBaseWindow, CNotifyPump)
DUI_ON_MSGTYPE(DUI_MSGTYPE_RETURN, OnKeyReturn)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelChanged)
DUI_ON_MSGTYPE(DUI_MSGTYPE_WINDOWINIT, OnWindowInited)
DUI_END_MESSAGE_MAP()

CBaseWindow::CBaseWindow()
{
}

LPCTSTR CBaseWindow::GetWindowClassName() const
{
	return _T("BaseWindow");
}

CDuiString CBaseWindow::GetSkinFile()
{
	return _T("app.xml");
}

LPCTSTR CBaseWindow::GetResourceID() const
{
	return MAKEINTRESOURCE(IDR_SKIN1X);
}

UILIB_RESOURCETYPE CBaseWindow::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
}

CDuiString CBaseWindow::GetSkinFolder()
{
	return _T("skin");
}

void CBaseWindow::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);

	//------
	//保存文件
	std::wstring str_savepath = CPaintManagerUI::GetInstancePath() + L"\\downloadedjson.dat";
	//将宽字符集转化为多字符集
	ofstream outFile(wstring2string(str_savepath), ios::out | ios::binary);
	for (int j = 0; j < m_downloaded_infor.size(); j++)
	{
		outFile.write((char*)&m_downloaded_infor[j], sizeof(Downloadedinfor));
	}
	outFile.close();
	//------

	BookmarkWindow::DestroyInstance();
	BookmarkMgrWindow::DestroyInstance();
	//CEF消息循环
	CefQuitMessageLoop();
}


void CBaseWindow::InitWindow()
{

	//------
	m_bIsjsoninit = true;
	//从文件中读取之前得保存得已下载信息
	std::wstring str_readpath = CPaintManagerUI::GetInstancePath() + L"\\downloadedjson.dat";
	//std::wstring str_readpath = L"D:\\downloadedjson.dat";
	Downloadedinfor readstruct;
	ifstream inFile(wstring2string(str_readpath), ios::in | ios::binary); //二进制读方式打开
	while (inFile.read((char *)&readstruct, sizeof(Downloadedinfor))) { //一直读到文件结束
		wstring sss = string2wstring(readstruct.SavePath);
		HANDLE hFile;//定义一个句柄。
		hFile = CreateFile(sss.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//使用CreatFile这个API函数打开文件
		if (!(hFile == INVALID_HANDLE_VALUE))
		{
			//文件存在
			m_downloaded_infor.push_back(readstruct);
		}//不存在就不push了
		CloseHandle(hFile);//关闭句柄
	}
	inFile.close();
	//------

	CefRefPtr<CefCookieManager> manager =
		CefCookieManager::GetGlobalManager(NULL);
	CefCookie cookie;
	CefString(&cookie.name).FromWString(L"Browser");
	CefString(&cookie.value).FromWString(L"WTBrowser");
	manager->SetCookie(CefString(wstring(L"http://localhost")), cookie, NULL);
	XBrowser::IEUtil::SetForceProcessIEVersion("IE8");
	m_CEFBrowser = new XBrowser::CCEFBrowserUI(GetHWND(), this);
	m_ContentView = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView")));
	m_ContentView->Add(m_CEFBrowser);
	m_MIEBrowser = new XBrowser::CMIEBrowserUI(GetHWND(), this, false);
	m_ContentView->Add(m_MIEBrowser);
	m_pContent = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("Content")));
	m_pAddressUI = static_cast<CEditUI*>(m_PaintManager.FindControl(L"location-edit")); //网址栏
	CVerticalLayoutUI* logo_text = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(L"logo_text"));
	//安装版本信息提醒
	logo_text->SetToolTip(L"WIN-TRUST SAFETY WORKBENCH VER 1.0");
	//隐藏证书按钮
	m_PaintManager.FindControl(_T("tool_cert"))->SetEnabled(false);
	/*m_PaintManager.FindControl(L"tool_switch")->SetEnabled(false);
	m_PaintManager.FindControl(L"SwitchLab")->SetVisible(false);*/

	//modify by yilanshuai 在窗口进行初始化的时候就已经创建了下载管理标签页,状态为不可见
	//创建下载管理标签页(不显示)
	//设置资源压缩包解压密码
	XBrowser::InsertResourceMap(L"wintrust", IDR_ZIPRES1, L"");
	//XBrowser::InsertResourceMap(L"wintrust", IDR_ZIPRES1, L"Webapp");
	downloadBundle = AddNewCEFTab(DownloadHtml);
	downloadBundle->tab->SetVisible(false);
	kp_isDownloadTabOpen = 0;
	//------

	CHECK(logo_text) << "logo_text NULL";
	CHECK(m_CEFBrowser) << "m_CEFBrowser NULL";
	CHECK(m_ContentView) << "m_ContentView NULL";
	CHECK(m_MIEBrowser) << "m_MIEBrowser NULL";
	CHECK(m_pContent) << "m_pContent NULL";
	CHECK(m_pAddressUI) << "m_pAddressUI NULL";
	m_bCloseCEF = false;
	//设置程序图标 路径在res的app.ico
	SetIcon(IDI_ICON);

	//add by yilanshuai 初始化时设置选择浏览器列表不可见
	CComboUI* pComboUI = static_cast<CComboUI*>(m_PaintManager.FindControl(L"ComboDemo1"));
	pComboUI->SetVisible(false);
}

//响应消息函数
LRESULT CBaseWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//LRESULT指的是从窗口程序或回调函数返回的32位值
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)//响应的消息类型
	{
	case WM_SHOWWINDOW://显示窗口
		if (wParam)
		{
			g_hHwndMain = this->GetHWND();//当前窗口的句柄
			g_KbHookData.nType = WH_KEYBOARD;//消息类型是键盘消息
			g_KbHookData.hkProc = KeyboardProc;//响应键盘操作
											   //SetWindowsHookEx参数列表
											   //__in int idHook, \\钩子类型

											   //__in HOOKPROC lpfn, \\回调函数地址

											   //	__in HINSTANCE hMod, \\实例句柄

											   //	__in DWORD dwThreadId); \\线程ID
			g_KbHookData.hHook = ::SetWindowsHookEx(g_KbHookData.nType, g_KbHookData.hkProc, (HINSTANCE)NULL, GetCurrentThreadId());
		}
		else
		{
			if (NULL != g_KbHookData.hHook)
			{
				//要删除的钩子的句柄
				//这里的hook参数是SetWindowsHookEx函数的返回值,函数成功，返回值为非零值
				//函数失败，返回值为0
				UnhookWindowsHookEx(g_KbHookData.hHook);
				g_KbHookData.hHook = NULL;
			}
		}
		break;
		//响应界面缩放
	case WM_DPICHANGED:
		OnDPIChanged(uMsg, wParam, lParam, bHandled);
		break;
		//拖动界面时，浏览器跟随窗口拖动
	case WM_MOVE:
		if (m_CEFBrowser)
		{
			m_CEFBrowser->Invalidate();
		}
		break;
		// 需要判断这里，如果去掉会导致关闭标签页后程序会退出
	case WM_CLOSE:
	{
		//只有一个页签的情况下，关闭这个页签回导致浏览器退出
		if (m_bCloseCEF)
		{
			m_bCloseCEF = false;
			bHandled = TRUE;
		}
		else
		{
			CefRefPtr<CefCookieManager> manager = CefCookieManager::GetGlobalManager(NULL);
			manager->FlushStore(NULL);
			DestroyWindow(GetHWND());
		}
	}
	break;
	case WM_COPYDATA:
		lRes = OnSetCookieData(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;
		break;
	}
	if (bHandled)
	{
		return lRes;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}


void CBaseWindow::OnKeyReturn(TNotifyUI& msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	if (sCtrlName == _T("location-edit"))
	{
		//获取location_edit存储的URL地址
		CHECK(m_pAddressUI) << "m_pAddressUI invalid";
		wstring location = m_pAddressUI->GetText().GetData();
		if (m_currentBundle)
		{
			//判断浏览器内核类型 标签页载入对应的URL地址
			if (m_currentBundle->type == BROWSER_TYPE_CEF)
			{
				m_CEFBrowser->LoadURL(m_currentBundle->browserid, location);
			}
			else
			{
				m_MIEBrowser->LoadURL(m_currentBundle->browserid, location);
			}
		}
		else
		{
			//当前URL的前缀
			auto type = kernel_type(location);
			if (type.empty() || type == Remote::RENDER_CONST_BLINK)
			{
				AddNewCEFTab(location);
			}
			else
			{
				AddNewMIETab(location, type);
			}
		}
	}
}

PFSMProvideUICBSelectClientCert CBaseWindow::GetSMCertCallback()
{
	return NULL;
}
PFSMProvideUICBPinInput CBaseWindow::GetSMPinCallback()
{
	return NULL;
}

void CBaseWindow::OnClick(TNotifyUI& msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
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
		//增加页签后默认选择焦点在新建的页签
		std::wstring ctrlName(sCtrlName.GetData());
		SelectTab(ctrlName.substr(11));
	}
	else if (sCtrlName.Find(_T("tab-close-"), 0) != -1)
	{
		//关闭页签
		std::wstring closeName(sCtrlName.GetData());
		CloseTab(closeName.substr(10));
	}
	else if (sCtrlName == _T("tool_back"))
	{
		auto bundle = m_currentBundle;
		if (bundle)
		{
			//后退功能，只能将当前页URL的子地址栏页面进行后退，新开页面无法使用后退功能
			if (bundle->type == BROWSER_TYPE_CEF)
			{
				m_CEFBrowser->GoBack(bundle->browserid);
			}
			else
			{
				m_MIEBrowser->GoBack(bundle->browserid);
			}
		}
	}
	else if (sCtrlName == _T("tool_forward"))
	{
		auto bundle = m_currentBundle;
		//获取当前页面后判断内核类型
		if (bundle)
		{
			//前进功能，与后退类似，只能在当前页URL的子地址栏页面进行前进，新开页面无法使用前进功能
			if (bundle->type == BROWSER_TYPE_CEF)
			{
				m_CEFBrowser->GoForward(bundle->browserid);
			}
			else
			{
				m_MIEBrowser->GoForward(bundle->browserid);
			}
		}
	}
	else if (sCtrlName == _T("tool_refresh"))
	{
		auto bundle = m_currentBundle;
		//获取当前页面类型后判断内核
		if (bundle)
		{
			//刷新页面功能
			if (bundle->type == BROWSER_TYPE_CEF)
			{
				m_CEFBrowser->ReLoad(bundle->browserid);
			}
			else
			{
				m_MIEBrowser->ReLoad(bundle->browserid);
			}
		}
	}
	else if (sCtrlName == _T("tool_sidebar"))
	{
		//获取当前页面句柄
		BookmarkWindow::GetInstance(m_hWnd)->ShowWindow(true, true);
		RECT rc;
		//返回当前窗口的边框矩形尺寸，尺寸以相对于屏幕坐标左上角的屏幕坐标给出
		GetWindowRect(m_hWnd, &rc);
		CVerticalLayoutUI *pAddr = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(L"tool_addr"));
		if (pAddr != nullptr)
		{
			bool bIsAddr = pAddr->IsVisible();
			if (bIsAddr)
				SetWindowPos(BookmarkWindow::GetInstance(m_hWnd)->GetHWND(), HWND_TOP,
					rc.left, rc.top + m_PaintManager.GetDPIObj()->Scale(80),
					m_PaintManager.GetDPIObj()->Scale(200),
					rc.bottom - rc.top - m_PaintManager.GetDPIObj()->Scale(80), SWP_NOZORDER);
			else
				SetWindowPos(BookmarkWindow::GetInstance(m_hWnd)->GetHWND(), HWND_TOP,
					rc.left, rc.top + m_PaintManager.GetDPIObj()->Scale(110),
					m_PaintManager.GetDPIObj()->Scale(200),
					rc.bottom - rc.top - m_PaintManager.GetDPIObj()->Scale(110), SWP_NOZORDER);
		}
	}
	//add by yilanshuai for SwitchCoreVersion
	else if (sCtrlName == L"tool_switch")
	{
		//获取浏览器当前内核版本
		auto bundle = m_currentBundle;
		if (bundle)
		{
			CButtonUI* pButtonUI = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"tool_switch"));
			CLabelUI* pLabelUI = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"SwitchLab"));
			CComboUI* pComboUI = static_cast<CComboUI*>(m_PaintManager.FindControl(L"ComboDemo1"));

			wstring location = m_pAddressUI->GetText().GetData();
			auto type = kernel_type(location);
			auto bundle = m_currentBundle;

			//如果是CEF内核，切换为IE内核
			if (bundle->type == BROWSER_TYPE_CEF)
			{
				pComboUI->SetVisible(true);
				AddNewMIETab(location, type);

				pLabelUI->SetText(L"兼容");
				pButtonUI->SetToolTip(L"当前为兼容模式,点击切换为高速模式");
				pButtonUI->SetNormalImage(L"toolbar\\compati_normal.png");
				pButtonUI->SetHotImage(L"toolbar\\compati_hover.png");
				pButtonUI->SetPushedImage(L"toolbar\\compati_pushed.png");
			}
			//如果是IE内核，切换为CEF
			else if (bundle->type == BROWSER_TYPE_MIE)
			{
				pComboUI->SetVisible(false);
				//CDuiString pDuiString = pComboUI->GetText();

				AddNewCEFTab(location);

				pLabelUI->SetText(L"高速");
				pButtonUI->SetToolTip(L"当前为高速模式,点击切换为兼容模式");
				pButtonUI->SetNormalImage(L"toolbar\\speed_normal.png");
				pButtonUI->SetHotImage(L"toolbar\\speed_hover.png");
				pButtonUI->SetPushedImage(L"toolbar\\speed_pushed.png");
			}
		}
	}
	else if (sCtrlName == L"tool_home")
	{
		BookmarkWindow::GetInstance(m_hWnd)->NavigateHomePage();
	}
	else if (sCtrlName == L"tool_bookmark")
	{
		//当前窗口的句柄
		auto bw = BookmarkMgrWindow::GetInstance(m_hWnd);
		bw->SetName(L"");
		bw->SetUrl(m_pAddressUI->GetText().GetData());
		bw->CenterWindow();
		bw->ShowWindow(true, true);
	}
	else if (sCtrlName == L"tool_clear")
	{
		//删除CEF缓存和IE本身缓存
		ClearCEFCache();
		ClearIECache();
		auto manager = CefCookieManager::GetGlobalManager(nullptr);
		//删除cookie数据
		manager->DeleteCookies(L"", L"", nullptr);
	}
	//------
	else if (sCtrlName == _T("tool_download"))
	{
		if (m_bIsjsoninit) // 初始化json
		{
			//从本地读取页面文件解析
			pushJsonToJS();// 把读出来的下载记录内容发给前端
			m_bIsjsoninit = false;
		}

		//显示下载页面
		downloadBundle->tab->SetVisible(true); // 显示
		SelectTab(downloadBundle->id); // 切换
		kp_isDownloadTabOpen = 1;
		//隐藏地址栏布局
		m_pAddressUI->SetVisible(false);
		SetAddrVisible(false);
	}
	//------
	else
	{
		__super::OnClick(msg);
	}
}

void CBaseWindow::OnSelChanged(TNotifyUI& msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	if (sCtrlName.Find(_T("tab-option-"), 0) != -1)
	{
		std::wstring ctrlName(sCtrlName.GetData());
		SelectTab(ctrlName.substr(11));
	}
	else if (sCtrlName.Find(_T("tab-close-"), 0) != -1)
	{
		std::wstring closeName(sCtrlName.GetData());
		CloseTab(closeName.substr(10));
	}
}

void CBaseWindow::OnWindowInited(TNotifyUI& msg)
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	BookmarkWindow::GetInstance(m_hWnd);
}

//#define NEWTAB_BUTTON
shared_ptr<BrowserBundle> CBaseWindow::MakeBundle(std::wstring id)
{
	if (id.empty())
	{
		id = GenUniqueId();
	}
	wstring stripName = wstring(L"Tabstrip-Browser");
	CHorizontalLayoutUI* tabstrip = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(stripName.c_str()));
	UINT index = tabstrip->GetCount();
	CContainerUI* pTab = new CContainerUI;
	std::wostringstream oss;
	oss << L"maxwidth=\"174\" name=\"tab-" << id << L"\"";
	pTab->SetAttributeList(oss.str().c_str());
	CDialogBuilder builder;
	builder.Create(_T("tab.xml"), (UINT)0, NULL, &m_PaintManager, pTab);
#if defined NEWTAB_BUTTON
	tabstrip->AddAt(pTab, index - 1);
#else
	tabstrip->AddAt(pTab, index);
#endif
	COptionUI* option = static_cast<COptionUI*>(m_PaintManager.FindSubControlByClass(pTab, _T("Option"), 0));
	option->SetName((std::wstring(L"tab-option-") + id).c_str());
	option->SetGroup(L"group-browser");
	option->SetText(L"新标签页");
	option->SetTextPadding({ 12, 0, 26, 0 });
	option->SetFont(0);
	CButtonUI* close = static_cast<CButtonUI*>(m_PaintManager.FindSubControlByClass(pTab, _T("Button"), 0));
	std::wostringstream closeAttributes;
	closeAttributes << L"name=\"tab-close-" << id << L"\"";
	close->SetAttributeList(closeAttributes.str().c_str());
	BrowserBundle* newBundle = new BrowserBundle(id);
	newBundle->closeButton = close;
	newBundle->tabButton = option;
	newBundle->tab = pTab;
	return shared_ptr<BrowserBundle>(newBundle);
}


shared_ptr<BrowserBundle> CBaseWindow::AddNewTab(std::wstring url, int appid)
{
	auto type = kernel_type(url);
	shared_ptr<BrowserBundle> bundle;
	if (type.empty() || type == Remote::RENDER_CONST_BLINK)
	{
		bundle = AddNewCEFTab(url, appid);
	}
	else
	{
		bundle = AddNewMIETab(url, type, appid);
	}
	return bundle;
}

//新建IE内核的标签页
shared_ptr<BrowserBundle> CBaseWindow::AddNewMIETab(std::wstring url, std::string ver, int appid, std::string postBytes)
{
	auto newBundle = MakeBundle();
	newBundle->type = BROWSER_TYPE_MIE;
	newBundle->browserid = m_MIEBrowser->NewPage(url, utf8_decode(ver));
	m_MIEBrowser->SetPostBytes(newBundle->browserid, postBytes);
	m_hashMIE.insert_or_assign(newBundle->browserid, newBundle);
	m_hashAll.insert_or_assign(newBundle->id, newBundle);
	SelectTab(newBundle->id);
	return newBundle;
}

//新建CEF内核的标签页
shared_ptr<BrowserBundle> CBaseWindow::AddNewCEFTab(std::wstring url, int appid)
{
	auto newBundle = MakeBundle();
	newBundle->type = BROWSER_TYPE_CEF;
	newBundle->browserid = m_CEFBrowser->NewPage(url);
	m_hashCEF.insert_or_assign(newBundle->browserid, newBundle);
	m_hashAll.insert_or_assign(newBundle->id, newBundle);
	SelectTab(newBundle->id);
	return newBundle;
}

//关闭页签时的处理(如果只剩下一个标签页的时候点击关闭该标签需不需要退出浏览器,当前的处理是关闭)
void CBaseWindow::CloseTab(std::wstring id)
{
	auto bundle = m_hashAll[id];
	if (bundle->type == BROWSER_TYPE_CEF)
	{

		if (bundle->browserid == downloadBundle->browserid) // 如果是下载管理标签
		{
			CHorizontalLayoutUI* tabStrip = static_cast<CHorizontalLayoutUI*>(bundle->tab->GetParent());
			CDuiPtrArray* options = m_PaintManager.FindSubControlsByClass(tabStrip, DUI_CTR_OPTION);
			if (options->GetSize() == 1) // 如果只剩下一个标签页（也就是下载tab）
			{
				tabStrip->Remove(bundle->tab, true); // 删除下载tab
				m_hashAll.erase(id);
			}
			else
			{
				downloadBundle->tab->SetVisible(false); // 存在多个页签时，自动隐藏下载tab
				kp_isDownloadTabOpen = 0;
				m_pAddressUI->SetVisible(true);
				SetAddrVisible(true);
			}

			// 下面的处理
			for (auto it : m_hashBookmark) // 左侧的侧边栏处理
			{
				if (bundle == it.second)
				{
					//链表容器使用earse删除节点，下一个元素的地址返回，下个节点自动往前移(内存擦除)
					m_hashBookmark.erase(it.first);
					break;
				}
			}
			//static_cast<CContainerUI*>(bundle->tab->GetParent())->Remove(bundle->tab, true);
			//m_hashAll.erase(id);
			if (m_currentBundle == bundle)
			{
				//FindSubControlByPoint 获取某控件下某位置的子控件对象
				//FindSubControlByName 获取某控件下指定名称的控件对象
				//FindSubControlByClass 获取某控件下指定类名的控件对象 + 重载版本获取指定类名查找控件集
				//GetSubControlsByClass 获取查找控件集
				auto options = m_PaintManager.FindSubControlsByClass(bundle->tab->GetParent(), DUI_CTR_OPTION);
				if (!options->IsEmpty())
				{
					COptionUI* tab = reinterpret_cast<COptionUI*>(options->GetAt(options->GetSize() - 1));
					if (tab)
					{
						tab->Selected(true);
					}
				}
				else
				{
					Close();
				}
			}

			return;
		}
		else
		{
			//关闭页签时，删除该页签，将下一页签往前移
			m_CEFBrowser->DelPage(bundle->browserid);
			m_hashCEF.erase(bundle->browserid);
		}
	}
	else
	{
		m_MIEBrowser->DelPage(bundle->browserid);
		m_hashMIE.erase(bundle->browserid);
	}

	for (auto it : m_hashBookmark)
	{
		if (bundle == it.second)
		{
			//
			m_hashBookmark.erase(it.first);
			break;
		}
	}

	CHorizontalLayoutUI* tabStrip = static_cast<CHorizontalLayoutUI*>(bundle->tab->GetParent());
	tabStrip->Remove(bundle->tab, true);

	m_hashAll.erase(id);
	//if (m_currentBundle == bundle)
	//{
	auto options = m_PaintManager.FindSubControlsByClass(tabStrip, DUI_CTR_OPTION);
	if (kp_isDownloadTabOpen == 1) // 下载标签页显示（代码走到此处，下载标签页必然存在，关闭下载标签页在上面已经处理）

	{
		// 正常切换
		COptionUI* tab = reinterpret_cast<COptionUI*>(options->GetAt(options->GetSize() - 1));
		if (tab)
		{
			tab->Selected(true);
		}
	}
	else // 下载标签页隐藏
	{
		if (options->GetSize() > 1) // 除了下载tab还有别的tab，切换到对应tab
		{
			COptionUI* tab = reinterpret_cast<COptionUI*>(options->GetAt(options->GetSize() - 1));
			if (tab)
			{
				tab->Selected(true);
			}
		}
		else { // 只剩下载tab
			tabStrip->Remove(bundle->tab, true); // 删除下载tab
			m_hashAll.erase(id);

			Close();
		}

	}
	//}
}
//------

LRESULT CBaseWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	LRESULT lRes = 0;
	switch (uMsg)
	{
	case WM_DEL_CURRENT_TAB:
		CloseTab(m_currentBundle->id);
		break;
	case WM_MAIN_MIE_CREATED:
		break;
	case WM_MAIN_MIE_CLOSED:
	{
		int browserid = wParam;
		auto bundle = m_hashMIE[browserid];
		if (bundle)
		{
			CloseTab(bundle->id);
		}
	}
	break;
	case WM_MAIN_MIE_DESTROY:
	{
		int browserid = wParam;
		if (PopCloseStore.find(browserid) != PopCloseStore.end())
		{
			// found
			CefRefPtr<CefProcessMessage> popupCloseMsg = CefProcessMessage::Create(_T("popupclose"));
			auto nMark = PopCloseStore[browserid].first;
			auto browser = PopCloseStore[browserid].second;
			popupCloseMsg->GetArgumentList()->SetInt(0, nMark);
			browser->SendProcessMessage(PID_RENDERER, popupCloseMsg);
			PopCloseStore.erase(browserid);
		}
		else
		{
			// not found
		}
	}
	break;
	case WM_MAIN_URL_CHANGE:
	{
		int browserid = wParam;
		wchar_t* pUrl = (wchar_t*)lParam;
		if (m_currentBundle == m_hashMIE[browserid])
		{
			m_pAddressUI->SetText(pUrl);
		}
	}
	break;
	case WM_MAIN_TITLE_CHANGE:
	{
		int browserid = wParam;
		wstring title = (wchar_t*)lParam;
		title = wstring(L"[IE]") + title;
		auto bundle = m_hashMIE[browserid];
		if (bundle && bundle->type == BROWSER_TYPE_MIE)
		{
			bundle->tabButton->SetText(title.c_str());
		}
	}
	break;
	case WM_MAIN_URL_BLOCKED_IE:
	{
		wchar_t* pUrl = (wchar_t*)lParam;
		AddNewCEFTab(pUrl);
	}
	break;
	case WM_MAIN_NEWVIEW_CREATED:
	{
		int browserid = wParam;
		auto newBundle = MakeBundle();
		newBundle->type = BROWSER_TYPE_MIE;
		newBundle->browserid = browserid;
		m_hashAll.insert_or_assign(newBundle->id, newBundle);
		m_hashMIE.insert_or_assign(browserid, newBundle);
		SelectTab(newBundle->id);
	}
	break;
	case WM_NAVIGATE_URL:
	{
		//点击导航栏
		int nIndex = wParam;
		if (m_hashBookmark[nIndex])
		{
			//标签页已经存在时，选择该标签页
			SelectTab(m_hashBookmark[nIndex]->id);
		}
		else
		{
			//标签页不存在时，新建标签页
			m_hashBookmark.insert_or_assign(nIndex, AddNewTab(BookmarkWindow::GetInstance(m_hWnd)->GetBookmarkUrl(nIndex)));
		}
	}
	break;
	default:
		bHandled = FALSE;
		break;
	}
	if (bHandled)
	{
		return lRes;
	}
	return __super::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
}


void CBaseWindow::SelectTab(std::wstring id)
{
	auto bundle = m_hashAll[id];
	if (bundle)
	{
		if (downloadBundle)
		{
			if (bundle->browserid == downloadBundle->browserid) // 如果是下载管理标签,隐藏地址栏布局
			{
				m_pAddressUI->SetVisible(false);
				SetAddrVisible(false);
			}
			else
			{
				m_pAddressUI->SetVisible(true);
				SetAddrVisible(true);
			}
		}
		bundle->tabButton->Selected(true, false);
		if (bundle->type == BROWSER_TYPE_CEF)
		{
			//判断浏览器内核类型是CEF还是IE
			m_CEFBrowser->ShowPage(bundle->browserid);
			m_ContentView->SelectItem(m_CEFBrowser);
			//获取该标签页的URL
			m_pAddressUI->SetText(m_CEFBrowser->GetFinalURL(bundle->browserid).c_str());
		}
		else
		{
			m_MIEBrowser->ShowPage(bundle->browserid);
			m_ContentView->SelectItem(m_MIEBrowser);
			m_pAddressUI->SetText(m_MIEBrowser->GetFinalURL(bundle->browserid).c_str());
		}
		//将当前页面设置为该页面
		m_currentBundle = bundle;
	}
}


void CBaseWindow::setDPI(int DPI)
{
	m_PaintManager.SetDPI(DPI);
	m_PaintManager.ResetDPIAssets();
	if (m_PaintManager.GetRoot() != NULL)
	{
		m_PaintManager.GetRoot()->NeedUpdate();
	}
}

LRESULT CBaseWindow::OnDPIChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_PaintManager.SetDPI(LOWORD(wParam));  // Set the new DPI, retrieved from the wParam
	m_PaintManager.ResetDPIAssets();
	int g_dpi = HIWORD(wParam);
	RECT* const prcNewWindow = (RECT*)lParam;
	SetWindowPos(m_hWnd,
		NULL,
		prcNewWindow->left,
		prcNewWindow->top,
		prcNewWindow->right - prcNewWindow->left,
		prcNewWindow->bottom - prcNewWindow->top,
		SWP_NOZORDER | SWP_NOACTIVATE);
	if (m_PaintManager.GetRoot() != NULL)
	{
		m_PaintManager.GetRoot()->NeedUpdate();
	}
	bHandled = false;
	return 0;
}



void CBaseWindow::OnBrowserClosing(CefRefPtr<CefBrowser> browser)
{
	auto bundle = m_hashCEF[browser->GetIdentifier()];
	if (bundle)
	{
		m_bCloseCEF = true;
		m_hashCEF.erase(bundle->browserid);
		for (auto it : m_hashBookmark)
		{
			if (bundle == it.second)
			{
				m_hashBookmark.erase(it.first);
				break;
			}
		}

		static_cast<CContainerUI*>(bundle->tab->GetParent())->Remove(bundle->tab, true);
		m_hashAll.erase(bundle->id);
		if (m_currentBundle == bundle)
		{
			auto options = m_PaintManager.FindSubControlsByClass(bundle->tab->GetParent(), DUI_CTR_OPTION);
			if (!options->IsEmpty())
			{
				COptionUI* tab = reinterpret_cast<COptionUI*>(options->GetAt(options->GetSize() - 1));
				if (tab)
				{
					tab->Selected(true);
				}
			}
			else
			{
				Close();
			}
		}
	}
}

void CBaseWindow::OnSetTitle(CefRefPtr<CefBrowser> browser, const std::wstring& title)
{
	int nBrowserID = browser->GetIdentifier();
	auto bundle = m_hashCEF[nBrowserID];
	if (bundle && bundle->type == BROWSER_TYPE_CEF && bundle->browserid == nBrowserID)
	{
		bundle->tabButton->SetText(title.c_str());
		return;
	}
}

void CBaseWindow::OnSetAddress(CefRefPtr<CefBrowser> browser, const wstring& url)
{
	static bool s_bReload = false;
	if (url == L"http://itoms.cmbc.com.cn/pasm/toIamPortal.htm?isSSo=yes")
	{
		if (!s_bReload)
		{
			s_bReload = true;
			browser->Reload();
		}
		else
		{
			s_bReload = false;
		}
	}

	if (m_currentBundle == m_hashCEF[browser->GetIdentifier()])
	{
		m_pAddressUI->SetText(url.c_str());
	}
}

void CBaseWindow::OnNewPage(const std::wstring& url)
{
	AddNewTab(url);
}

void CBaseWindow::OnUrlBlocked(const std::wstring& url)
{
	auto type = kernel_type(url);
	AddNewMIETab(url, type);
}

void CBaseWindow::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	//------
	// 文件消息处理
	std::string strMsg = message->GetName();
	string::size_type idx;
	idx = strMsg.find("changestate");//是否有改变状态
	if (!(idx == string::npos)) {
		Changestate Changestate_vector;
		std::string::size_type nPos1 = std::string::npos;
		nPos1 = strMsg.find_last_of(",");
		std::string strValue = "";
		if (nPos1 != -1)
		{
			strValue = strMsg.substr(nPos1 + 1, strMsg.length() - nPos1);
			Changestate_vector.StateIndex = atoi(strValue.c_str());
			strMsg = strMsg.substr(0, nPos1);
		}

		nPos1 = strMsg.find_last_of(",");
		if (nPos1 != -1)
		{
			strValue = strMsg.substr(nPos1 + 1, strMsg.length() - nPos1);
			Changestate_vector.Fileid = atoi(strValue.c_str());
		}
		m_changestatevector.push_back(Changestate_vector);
	}
	//string::size_type idx;
	idx = strMsg.find("deleteDownloadFile");//是否删除了下载的文件
	if (!(idx == string::npos)) {

		std::string::size_type nPos1 = std::string::npos;
		nPos1 = strMsg.find_last_of(",");
		std::string strValue = "";
		if (nPos1 != -1)
		{
			strValue = strMsg.substr(nPos1 + 1, strMsg.length() - nPos1);
			int ndelID = atoi(strValue.c_str());

			for (int i = 0; i < m_downloaded_infor.size(); i++)
			{
				if (ndelID == m_downloaded_infor[i].nID)
				{
					m_downloaded_infor.erase(m_downloaded_infor.begin() + i);//删除对应的vector
				}
			}
		}
	}
	//------

	if (message->GetName() == _T("popup"))
	{
		wstring url = message->GetArgumentList()->GetString(0).ToWString();
		wstring type = message->GetArgumentList()->GetString(1).ToWString();
		wstring external = message->GetArgumentList()->GetString(2).ToWString();
		auto left = message->GetArgumentList()->GetInt(3);
		auto top = message->GetArgumentList()->GetInt(4);
		auto width = message->GetArgumentList()->GetInt(5);
		auto height = message->GetArgumentList()->GetInt(6);
		int nMark = message->GetArgumentList()->GetInt(7);
		int browserid = m_MIEBrowser->NewPage(url, type, true, left, top, width, height);
		m_MIEBrowser->SetExternalData(browserid, external);
		PopCloseStore.insert_or_assign(browserid, std::make_pair(nMark, browser));
	}
	else if (message->GetName() == L"blocked")
	{
		string url = message->GetArgumentList()->GetString(0);
		string post = message->GetArgumentList()->GetString(1);
		string type = kernel_type(utf8_decode(url));
		if (post.empty())
		{
			AddNewMIETab(utf8_decode(url), type);
		}
		else
		{
			AddNewMIETab(utf8_decode(url), type, -1, ws2s(utf8_decode(post)));
		}
	}
	else if (message->GetName() == L"alertWnd")
	{
		auto args = message->GetArgumentList();
		CTipMsgWnd::MessageBox(GetHWND(), L"提示", L"指定文件不存在", MB_OK);
	}
}

void CBaseWindow::OnPopupCreated(CefRefPtr<CefBrowser> browser)
{
	int browserid = browser->GetIdentifier();
	HWND hBrowserWnd = browser->GetHost()->GetWindowHandle();
	auto newBundle = MakeBundle();
	newBundle->type = BROWSER_TYPE_CEF;
	newBundle->browserid = browserid;
	m_hashCEF.insert_or_assign(newBundle->browserid, newBundle);
	m_hashAll.insert_or_assign(newBundle->id, newBundle);
	SelectTab(newBundle->id);
}

//------

//判断字符串是否包含某字符串
//@params:str:大的字符串
//@params:contains_str:所包含的字符串
//@return: false:未包含 true：包含
BOOL  IsContainsStr(string str, string contains_str)
{
	string::size_type idx = str.find(contains_str);
	if (idx != string::npos)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//------

void CBaseWindow::OnBeforeDownload(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	const CefString& suggested_name,
	CefRefPtr<CefBeforeDownloadCallback> callback)
{
	//callback->Continue("", true);

	//------
	//初始化下载状态，默认是resume
	Downloadingstate filestate;
	filestate.Fileid = download_item->GetId();
	filestate.strstate = DownloadStateType[1];
	m_downloadingstate.push_back(filestate);

	//显示下载页面
	downloadBundle->tab->SetVisible(true); // 显示
	SelectTab(downloadBundle->id); // 切换
	kp_isDownloadTabOpen = 1;

	WCHAR sMyDocuPath[800] = { 0 };
	::SHGetSpecialFolderPathW(0, sMyDocuPath, CSIDL_PROFILE, 0);

	//如果有重复名字（思想：要下载的去掉后缀 和 已存在的去掉括号和后缀 进行比较，如果有重复的就在 已存在的文件后面加(i)）
	wstring wstrExt = suggested_name.ToWString();
	string::size_type position = wstrExt.find(L".");
	string strExt = wstring2string(wstrExt);
	string yaoxiazaidequdiaohouzhui = strExt.substr(0, position);
	string houzhui = strExt.substr(position, strExt.size() - 1);

	int i = 0;
	char count[32];

	//for (int a = 0; a < m_downloaded_infor.size(); a++)
	//{
	//	string yicundemingzi = m_downloaded_infor[a].filename;
	//	string qudiaokuohao = yicundemingzi.substr(0, position); 
	//	
	//	if (0 == strcmp(qudiaokuohao.c_str(), yaoxiazaidequdiaohouzhui.c_str()))
	//	{
	//		i++;
	//		
	//		qudiaokuohao.insert(position, "(");
	//		_itoa(i, count, 10);
	//		qudiaokuohao.insert(position + 1, count);
	//		qudiaokuohao.insert(position + 2, ")");
	//		qudiaokuohao += houzhui;
	//		wstrExt = string2wstring(qudiaokuohao);
	//	}
	//}

	int number = 0;
	for (int a = 0; a < m_downloaded_infor.size(); a++)
	{
		string yicundemingzi = m_downloaded_infor[a].filename;
		string qudiaokuohao = yicundemingzi.substr(0, position);
		string::size_type position2 = wstrExt.find(L".");
		if (IsContainsStr(yicundemingzi, "(") && IsContainsStr(yicundemingzi, ")")) // 如果包含（）
		{
			string numberString = yicundemingzi.substr(position2 - 2, position2 - 1);
			int y = atoi(numberString.c_str());
			if (y > number)
			{
				number = y;
			}
			number++;

			qudiaokuohao.insert(position, "(");
			_itoa(number, count, 10);
			qudiaokuohao.insert(position + 1, count);
			qudiaokuohao.insert(position + 2, ")");
			qudiaokuohao += houzhui;
			wstrExt = string2wstring(qudiaokuohao);
		}
		else
		{
			if (0 == strcmp(qudiaokuohao.c_str(), yaoxiazaidequdiaohouzhui.c_str()))
			{
				qudiaokuohao.insert(position, "(");
				_itoa(i, count, 10);
				qudiaokuohao.insert(position + 1, "1");
				qudiaokuohao.insert(position + 2, ")");
				qudiaokuohao += houzhui;
				wstrExt = string2wstring(qudiaokuohao);
			}

		}
	}

	wstring sDownloadPath = sMyDocuPath;
	sDownloadPath += L"\\Downloads\\";
	sDownloadPath += wstrExt;

	CefString sPath;
	sPath.FromWString(sDownloadPath);

	callback->Continue(sDownloadPath, false);//第一个参数是设置文件保存全路径包含文件名
											 //------
}



//------
wstring CBaseWindow::string2wstring(string str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';//添加字符串结尾
	result.append(buffer);
	delete[] buffer;//删除缓冲区并返回值 
	return result;
}

//将wstring转换成string  
string CBaseWindow::wstring2string(wstring wstr)
{
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

// 替换字符串，空格替换为 "," ，前面加上 ["，后面加上 "]
std::string string_replace(string &st1, char c)
{
	string::iterator tmp = find(st1.begin(), st1.end(), c);
	while (tmp != st1.end())
	{
		auto x = st1.erase(tmp);
		st1.insert(x, '\"');
		st1.insert(x, ',');
		st1.insert(x, '\"');
		tmp = find(x, st1.end(), c);
	}

	st1.insert(st1.begin(), '"');
	st1.insert(st1.begin(), '[');
	st1.insert(st1.end(), '"');
	st1.insert(st1.end(), ']');

	return st1;
}
//------

void CBaseWindow::OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	CefRefPtr<CefDownloadItemCallback> callback)
{
	//------
	std::string str_downloadstate;
	string strpath = wstring2string(download_item->GetFullPath());
	bool bIschange = false;
	int a = m_changestatevector.size();

	for (int i = 0; i < m_changestatevector.size(); i++)
	{
		if (download_item->GetId() == m_changestatevector[i].Fileid)
		{
			switch (m_changestatevector[i].StateIndex)
			{
			case DOWNLOADING_STATE_PAUSE:
				bIschange = true;
				str_downloadstate = DownloadStateType[DOWNLOADING_STATE_PAUSE];
				callback->Pause();
				break;
			case DOWNLOADING_STATE_RESUME:
				bIschange = true;
				str_downloadstate = DownloadStateType[DOWNLOADING_STATE_RESUME];
				callback->Resume();
				break;
			case DOWNLOADING_STATE_CANCEL:
				bIschange = true;
				str_downloadstate = DownloadStateType[DOWNLOADING_STATE_CANCEL];
				callback->Cancel();
				break;
			default:
				break;
			}
			m_changestatevector.erase(m_changestatevector.begin() + i);

		}
	}

	for (int j = 0; j < m_downloadingstate.size(); j++)
	{
		if (download_item->GetId() == m_downloadingstate[j].Fileid)
		{
			if (bIschange)//状态有变化需要更新自己记录的结构体
			{
				m_downloadingstate[j].strstate = str_downloadstate;
				return;//把下载状态赋值之后再return
			}
			else
			{
				str_downloadstate = m_downloadingstate[j].strstate;
			}

			if (download_item->IsCanceled() || download_item->IsComplete())
			{
				m_downloadingstate.erase(m_downloadingstate.begin() + j);
			}
		}
	}
	if (strpath != "")
	{
		std::string::size_type nPos1 = std::string::npos;
		nPos1 = strpath.find_last_of("\\");
		string strname = strpath.substr(nPos1 + 1, strpath.length() - nPos1);
		std::string  str_return = "";
		Json::Value value;
		value["nID"] = download_item->GetId();
		value["filename"] = strname;
		value["bytesReceived"] = FormatINT2STR(download_item->GetReceivedBytes());
		value["totalBytes"] = FormatINT2STR(download_item->GetTotalBytes());
		value["bIsComplete"] = download_item->IsComplete();
		value["state"] = str_downloadstate;
		value["StartTime"] = FormatUTC2BJ(download_item->GetStartTime());
		value["EndTime"] = FormatUTC2BJ(download_item->GetEndTime());
		value["SavePath"] = strpath;
		std::string str_json = value.toStyledString();
		wstring wstr_json = string2wstring(str_json);
		//if (kp_isDownloadTabOpen != 0) {

		////如果有重复名字
		//wstring wstrExt = string2wstring(strname);
		//string::size_type position = wstrExt.find(L".");
		//int i = 0;
		//char count[32];
		//string yaoxiazaidequdiaohouzhui = strname.substr(0, position);
		//string houzhui = strname.substr(position, strname.size() - 1);
		//for (int a = 0; a < m_downloaded_infor.size(); a++)
		//{
		//	string yicundemingzi = m_downloaded_infor[a].filename;
		//	string qudiaokuohao = yicundemingzi.substr(0, position); 

		//	if (0 == strcmp(qudiaokuohao.c_str(), yaoxiazaidequdiaohouzhui.c_str()))
		//	{
		//		i++;
		//		
		//		qudiaokuohao.insert(position, "(");
		//		_itoa(i, count, 10);
		//		qudiaokuohao.insert(position + 1, count);
		//		qudiaokuohao.insert(position + 2, ")");
		//		qudiaokuohao += houzhui;
		//		value["filename"] = qudiaokuohao;
		//	}
		//}


		CefRefPtr<CefFrame> frame = m_CEFBrowser->GetBrowser(downloadBundle->browserid)->GetMainFrame();
		frame->ExecuteJavaScript(L"if(typeof(DownloadUpdated) === 'function') {DownloadUpdated(" + wstr_json + L");}", DownloadHtml, 0);
		//}

		//当下载已经完成的时候，将下载文件的信息存到vector容器中
		if (download_item->IsComplete())
		{
			////如果有重复名字的先清除之前的记录
			//for (int a = 0; a < m_downloaded_infor.size(); a++)
			//{
			//	if (0 == strcmp(m_downloaded_infor[a].filename, strname.c_str()))
			//	{
			//		//m_downloaded_infor.erase(m_downloaded_infor.begin() + a);
			//		strname += "(1)";
			//		value["filename"] = strname;
			//	}
			//}
			//添加新的记录
			Downloadedinfor finishfileinfor;
			if (m_downloaded_infor.empty())
			{
				finishfileinfor.nID = 1;
			}
			else
			{
				finishfileinfor.nID = m_downloaded_infor[m_downloaded_infor.size() - 1].nID + 1;
			}
			strcpy(finishfileinfor.filename, strname.c_str());
			strcpy(finishfileinfor.bytesReceived, FormatINT2STR(download_item->GetReceivedBytes()).c_str());
			strcpy(finishfileinfor.totalBytes, FormatINT2STR(download_item->GetTotalBytes()).c_str());
			finishfileinfor.bIsComplete = true;
			strcpy(finishfileinfor.state, str_downloadstate.c_str());
			strcpy(finishfileinfor.StartTime, FormatUTC2BJ(download_item->GetStartTime()).c_str());
			strcpy(finishfileinfor.EndTime, FormatUTC2BJ(download_item->GetEndTime()).c_str());
			strcpy(finishfileinfor.SavePath, strpath.c_str());
			m_downloaded_infor.push_back(finishfileinfor);//push进容器

			value["nID"] = finishfileinfor.nID;
			str_json = value.toStyledString();
			wstr_json = string2wstring(str_json);
			//if (kp_isDownloadTabOpen != 0) {
			CefRefPtr<CefFrame> frame = m_CEFBrowser->GetBrowser(downloadBundle->browserid)->GetMainFrame();
			frame->ExecuteJavaScript(L"if(typeof(UpdateDownloadedJsonArry) === 'function') {UpdateDownloadedJsonArry(" + wstr_json + L");}", DownloadHtml, 0);
			//}
		}
	}
	//------
}

//------
//格式化时间
std::string CBaseWindow::FormatUTC2BJ(CefTime cef_time)
{
	std::stringstream str_stream;
	std::stringstream str_stream_zero;
	std::string  strformat = "";

	time_t gettime = cef_time.GetTimeT();
	struct tm *pFormatime;
	//time(&gettime); /*获得time_t结构的时间，UTC时间*/
	pFormatime = localtime(&gettime); /*转换为struct tm结构的当地时间*/

	int nh_m_s_time = pFormatime->tm_hour;
	std::string str_hour = "";
	if (nh_m_s_time < 10)
	{
		str_stream_zero << "0" << pFormatime->tm_hour;
	}
	else
	{
		str_stream_zero << pFormatime->tm_hour;
	}
	str_hour = str_stream_zero.str();
	str_stream_zero.str("");

	nh_m_s_time = pFormatime->tm_min;
	std::string str_min = "";
	if (nh_m_s_time < 10)
	{
		str_stream_zero << "0" << pFormatime->tm_min;
	}
	else
	{
		str_stream_zero << pFormatime->tm_min;
	}
	str_min = str_stream_zero.str();
	str_stream_zero.str("");

	nh_m_s_time = pFormatime->tm_sec;
	std::string str_sec = "";
	if (nh_m_s_time < 10)
	{
		str_stream_zero << "0" << pFormatime->tm_sec;
	}
	else
	{
		str_stream_zero << pFormatime->tm_sec;
	}
	str_sec = str_stream_zero.str();
	str_stream_zero.str("");

	str_stream << 1900 + pFormatime->tm_year << "-" << 1 + pFormatime->tm_mon << "-" << pFormatime->tm_mday << " " << str_hour << ":" << str_min << ":" << str_sec;
	strformat = str_stream.str();

	str_stream.str("");
	return strformat;
}

//int转string
std::string CBaseWindow::FormatINT2STR(int64 ndata)
{
	std::stringstream str_stream;
	std::string  str_format = "";

	str_stream << ndata;
	str_format = str_stream.str();
	str_stream.str("");
	return str_format;
}

//把已完成的json发到js
void CBaseWindow::pushJsonToJS()
{
	//if (kp_isDownloadTabOpen == 0) return;

	CefRefPtr<CefFrame> frame = m_CEFBrowser->GetBrowser(downloadBundle->browserid)->GetMainFrame();
	Json::Value value;
	for (int j = 0; j < m_downloaded_infor.size(); j++)
	{
		value["nID"] = m_downloaded_infor[j].nID;
		value["filename"] = m_downloaded_infor[j].filename;
		value["bytesReceived"] = m_downloaded_infor[j].bytesReceived;
		value["totalBytes"] = m_downloaded_infor[j].totalBytes;
		value["bIsComplete"] = m_downloaded_infor[j].bIsComplete;
		value["state"] = m_downloaded_infor[j].state;
		value["StartTime"] = m_downloaded_infor[j].StartTime;
		value["EndTime"] = m_downloaded_infor[j].EndTime;
		value["SavePath"] = m_downloaded_infor[j].SavePath;

		std::string str_json = value.toStyledString();
		wstring wstr_json = string2wstring(str_json);
		frame->ExecuteJavaScript(L"if(typeof(DownloadJsonInit) === 'function') {DownloadJsonInit(" + wstr_json + L");}", DownloadHtml, 0);
	}
	frame->ExecuteJavaScript(L"if(typeof(initList) === 'function') {initList();}", DownloadHtml, 0);
}
//------

// IE的delegate不是在主线程中处理的，需要发送消息给主线程处理
void CBaseWindow::OnIECreated(int browserid)
{
	SendMessage(WM_MAIN_MIE_CREATED, browserid);
}

void CBaseWindow::OnIEClosed(int browserid)
{
	SendMessage(WM_MAIN_MIE_CLOSED, browserid);
}

void CBaseWindow::OnIEDestroyed(int browserid)
{
	SendMessage(WM_MAIN_MIE_DESTROY, browserid);
}

void CBaseWindow::OnSetIEURL(int browserid, const std::wstring& url)
{
	SendMessage(WM_MAIN_URL_CHANGE, browserid, (LPARAM)url.c_str());
}
void CBaseWindow::OnSetIETitle(int browserid, const std::wstring& title)
{
	SendMessage(WM_MAIN_TITLE_CHANGE, browserid, (LPARAM)title.c_str());
}

void CBaseWindow::OnUrlBlocked(int browserid, const std::wstring& url)
{
	SendMessage(WM_MAIN_URL_BLOCKED_IE, browserid, (LPARAM)url.c_str());
}

void CBaseWindow::OnNewViewCreated(int browserid)
{
	SendMessage(WM_MAIN_NEWVIEW_CREATED, browserid, NULL);
}

void CBaseWindow::OnNeedCookie(HWND hRenderWnd, wstring url, HANDLE hEvent)
{
	CefRefPtr<CefCookieManager> manager =
		CefCookieManager::GetGlobalManager(NULL);
	CefRefPtr<XBrowser::CCookieVisitor> CookieVisitor = new XBrowser::CCookieVisitor(hEvent, hRenderWnd, url);
	bool state = manager->VisitAllCookies(CookieVisitor);
	manager->FlushStore(NULL);
}


LRESULT CBaseWindow::OnSetCookieData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND handle = (HWND)wParam;
	bool needIst = true;
	COPYDATASTRUCT* pCopyDataStruct = (COPYDATASTRUCT*)lParam;
	//直接把结构体里的参数取出来调用InternetSetCookieExW设置Cookie
	CookieData* pData = static_cast<CookieData*>(pCopyDataStruct->lpData);
	wchar_t* pszUrl = NULL, *pszCookieName = NULL, *pszCookieData = NULL;
	if (pData != NULL)
	{
		if (pData->dwSizeUrl > 0)
		{
			pszUrl = reinterpret_cast<wchar_t*>(pData->pStrData);
		}
		if (pData->dwSizeCookieName > 0)
		{
			pszCookieName = reinterpret_cast<wchar_t*>((pData->pStrData + pData->dwSizeUrl));
		}
		if (pData->dwSizeCookieData > 0)
		{
			pszCookieData = reinterpret_cast<wchar_t*>((pData->pStrData + pData->dwSizeUrl + pData->dwSizeCookieName));
		}
		//m_MIEBrowser->SetCookie(pCopyDataStruct);
		if (handle != 0)
		{
			needIst = false;
			//setCookie = false;
			CefRefPtr<CefCookieManager> manager =
				CefCookieManager::GetGlobalManager(NULL);
			wstring url = pszUrl;// wcsstr(pszUrl, L"//") + 2;
			wstring cookieContent = pszCookieData;
			vector<std::wstring> cookieItem = SplitW(pszCookieData, L";");
			{
				CefCookie cookie;
				if (cookieItem.size() > 0)
				{
					CefString(&cookie.name).FromWString(cookieItem.at(0).substr(0, cookieItem.at(0).find(L"=")));
					CefString(&cookie.value).FromWString(cookieItem.at(0).substr(cookieItem.at(0).find(L"=") + 1, cookieItem.at(0).size() - cookieItem.at(0).find(L"=") - 1));
				}
				if (cookieContent.find(L"domain") == wstring::npos)
				{
					CefString(&cookie.domain).FromWString(url);
				}
				else
				{
					wstring domain = wcsstr(pszCookieData, L"domain=") + 7;
					domain = domain.substr(0, domain.find(L";"));
					CefString(&cookie.domain).FromWString(domain);
				}
				if (cookieContent.find(L"httponly") != wstring::npos)
				{
					cookie.httponly = true;
				}
				CefString(&cookie.path).FromASCII("/");
				if (cookieContent.find(L"expires") != wstring::npos || cookieContent.find(L"Expires") != wstring::npos)
				{
					__time32_t  lTime = time(nullptr);
					tm          t;
					_localtime32_s(&t, &lTime);
					size_t index = cookieContent.find(L"expires") + 8;
					if (index <= 8)
					{
						index = cookieContent.find(L"Expires") + 8;
					}
					cookieContent = cookieContent.substr(index, cookieContent.find(L"GMT") - 10 - index);
					cookieContent = cookieContent.substr(cookieContent.find_last_of(L"-") + 1, cookieContent.size());
					wstringstream ss;
					ss << cookieContent;
					int date;
					ss >> date;
					//int date = _wtoi(cookieContent.c_str());
					if (date >= (t.tm_year + 1900))
					{
						//MessageBox(NULL, cookieContent.data(), L"123", MB_OK);
						cookie.has_expires = true;
						cookie.expires.year = date + 10;
						cookie.expires.month = 1;
						cookie.expires.day_of_week = 1;
						cookie.expires.day_of_month = 1;
					}
					else
					{
						cookieContent = pszCookieData;
						cookieContent.substr(index);
						//MessageBox(NULL, cookieContent.data(), L"321", MB_OK);
						cookie.has_expires = true;
						cookie.expires.year = date;
						cookie.expires.month = 1;
						cookie.expires.day_of_week = 1;
						cookie.expires.day_of_month = 1;
					}
				}
				bool state = manager->SetCookie(CefString(wstring(L"http://").append(pszUrl)), cookie, NULL);
			}
		}
	}
	return 0;
}

void CBaseWindow::SetAddrVisible(bool bShow)
{
	//显示/隐藏地址栏布局
	CVerticalLayoutUI *pAddr = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(L"tool_addr"));
	if (pAddr != nullptr)
	{
		bool bIsAddr = pAddr->IsVisible();
		if (bShow != bIsAddr)
			pAddr->SetVisible(bShow);
	}
	//启用/禁用前进、后退、刷新
	CButtonUI *pBack = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"tool_back"));
	CButtonUI *pForward = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"tool_forward"));
	CButtonUI *pRefresh = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"tool_refresh"));
	if (pBack != nullptr && pForward != nullptr && pRefresh != nullptr)
	{
		bool bEnabled = false;
		if (bShow)
		{
			bEnabled = pBack->IsEnabled();
			if (!bEnabled)
				pBack->SetEnabled(bShow);

			bEnabled = pForward->IsEnabled();
			if (!bEnabled)
				pForward->SetEnabled(bShow);

			bEnabled = pRefresh->IsEnabled();
			if (!bEnabled)
				pRefresh->SetEnabled(bShow);
		}
		else
		{
			bEnabled = pBack->IsEnabled();
			if (bEnabled)
				pBack->SetEnabled(bShow);

			bEnabled = pForward->IsEnabled();
			if (bEnabled)
				pForward->SetEnabled(bShow);

			bEnabled = pRefresh->IsEnabled();
			if (bEnabled)
				pRefresh->SetEnabled(bShow);
		}
	}
}