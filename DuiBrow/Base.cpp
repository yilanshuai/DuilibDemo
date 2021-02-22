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

/// Hook���̲���������,Ctrl+Wʱ��������Ϣ�����ڣ��رյ�ǰ��ǩҳ

TAG_HOOK_DATA g_KbHookData;
HWND g_hHwndMain = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//if (0 == nCode)
	//{
	//	switch (wParam)
	//	{
	//		// 'W' ���̵�16����ASCII��
	//	case 0x57:
	//	{
	//		// �жϰ���״̬
	//		// �ο� https://docs.microsoft.com/zh-cn/previous-versions/windows/desktop/legacy/ms644984(v=vs.85)
	//		if ((HIWORD(lParam) & 0xC000) == 0)
	//		{
	//			// ������Ч
	//			if (NULL != g_hHwndMain)
	//			{
	//				// Ctrl���Ѿ�����
	//				if (GetKeyState(VK_CONTROL) < 0)
	//				{
	//					PostMessage(g_hHwndMain, WM_DEL_CURRENT_TAB, 0, 0);
	//				}

	//			}
	//		}
	//	}
	//	break;

		//add by yilanshuai for ��ݼ�CTRL+D �����ղ�
		//'D'���̵�16����ASCII��
		//case 0x44:
		//{
		//	if ((HIWORD(lParam) & 0xC000) == 0)
		//	{
		//		if (NULL != g_hHwndMain)
		//		{
		//			if (GetKeyState(VK_CONTROL) < 0)
		//			{
		//				//��ǰ���ڵľ��
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

		//add by yilanshuai for ��ݼ�ALT+N �½���ǩҳ
		//'N'���̵�16����ASCII��
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


// �Ϻ�������ֽ��������ӣ�����������Ϣ���棬�ڵ������ڹر��Ժ���Ϣ���͸�CEF����
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
	//�����ļ�
	std::wstring str_savepath = CPaintManagerUI::GetInstancePath() + L"\\downloadedjson.dat";
	//�����ַ���ת��Ϊ���ַ���
	ofstream outFile(wstring2string(str_savepath), ios::out | ios::binary);
	for (int j = 0; j < m_downloaded_infor.size(); j++)
	{
		outFile.write((char*)&m_downloaded_infor[j], sizeof(Downloadedinfor));
	}
	outFile.close();
	//------

	BookmarkWindow::DestroyInstance();
	BookmarkMgrWindow::DestroyInstance();
	//CEF��Ϣѭ��
	CefQuitMessageLoop();
}


void CBaseWindow::InitWindow()
{

	//------
	m_bIsjsoninit = true;
	//���ļ��ж�ȡ֮ǰ�ñ������������Ϣ
	std::wstring str_readpath = CPaintManagerUI::GetInstancePath() + L"\\downloadedjson.dat";
	//std::wstring str_readpath = L"D:\\downloadedjson.dat";
	Downloadedinfor readstruct;
	ifstream inFile(wstring2string(str_readpath), ios::in | ios::binary); //�����ƶ���ʽ��
	while (inFile.read((char *)&readstruct, sizeof(Downloadedinfor))) { //һֱ�����ļ�����
		wstring sss = string2wstring(readstruct.SavePath);
		HANDLE hFile;//����һ�������
		hFile = CreateFile(sss.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//ʹ��CreatFile���API�������ļ�
		if (!(hFile == INVALID_HANDLE_VALUE))
		{
			//�ļ�����
			m_downloaded_infor.push_back(readstruct);
		}//�����ھͲ�push��
		CloseHandle(hFile);//�رվ��
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
	m_pAddressUI = static_cast<CEditUI*>(m_PaintManager.FindControl(L"location-edit")); //��ַ��
	CVerticalLayoutUI* logo_text = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(L"logo_text"));
	//��װ�汾��Ϣ����
	logo_text->SetToolTip(L"WIN-TRUST SAFETY WORKBENCH VER 1.0");
	//����֤�鰴ť
	m_PaintManager.FindControl(_T("tool_cert"))->SetEnabled(false);
	/*m_PaintManager.FindControl(L"tool_switch")->SetEnabled(false);
	m_PaintManager.FindControl(L"SwitchLab")->SetVisible(false);*/

	//modify by yilanshuai �ڴ��ڽ��г�ʼ����ʱ����Ѿ����������ع����ǩҳ,״̬Ϊ���ɼ�
	//�������ع����ǩҳ(����ʾ)
	//������Դѹ������ѹ����
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
	//���ó���ͼ�� ·����res��app.ico
	SetIcon(IDI_ICON);

	//add by yilanshuai ��ʼ��ʱ����ѡ��������б��ɼ�
	CComboUI* pComboUI = static_cast<CComboUI*>(m_PaintManager.FindControl(L"ComboDemo1"));
	pComboUI->SetVisible(false);
}

//��Ӧ��Ϣ����
LRESULT CBaseWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//LRESULTָ���ǴӴ��ڳ����ص��������ص�32λֵ
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)//��Ӧ����Ϣ����
	{
	case WM_SHOWWINDOW://��ʾ����
		if (wParam)
		{
			g_hHwndMain = this->GetHWND();//��ǰ���ڵľ��
			g_KbHookData.nType = WH_KEYBOARD;//��Ϣ�����Ǽ�����Ϣ
			g_KbHookData.hkProc = KeyboardProc;//��Ӧ���̲���
											   //SetWindowsHookEx�����б�
											   //__in int idHook, \\��������

											   //__in HOOKPROC lpfn, \\�ص�������ַ

											   //	__in HINSTANCE hMod, \\ʵ�����

											   //	__in DWORD dwThreadId); \\�߳�ID
			g_KbHookData.hHook = ::SetWindowsHookEx(g_KbHookData.nType, g_KbHookData.hkProc, (HINSTANCE)NULL, GetCurrentThreadId());
		}
		else
		{
			if (NULL != g_KbHookData.hHook)
			{
				//Ҫɾ���Ĺ��ӵľ��
				//�����hook������SetWindowsHookEx�����ķ���ֵ,�����ɹ�������ֵΪ����ֵ
				//����ʧ�ܣ�����ֵΪ0
				UnhookWindowsHookEx(g_KbHookData.hHook);
				g_KbHookData.hHook = NULL;
			}
		}
		break;
		//��Ӧ��������
	case WM_DPICHANGED:
		OnDPIChanged(uMsg, wParam, lParam, bHandled);
		break;
		//�϶�����ʱ����������洰���϶�
	case WM_MOVE:
		if (m_CEFBrowser)
		{
			m_CEFBrowser->Invalidate();
		}
		break;
		// ��Ҫ�ж�������ȥ���ᵼ�¹رձ�ǩҳ�������˳�
	case WM_CLOSE:
	{
		//ֻ��һ��ҳǩ������£��ر����ҳǩ�ص���������˳�
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
		//��ȡlocation_edit�洢��URL��ַ
		CHECK(m_pAddressUI) << "m_pAddressUI invalid";
		wstring location = m_pAddressUI->GetText().GetData();
		if (m_currentBundle)
		{
			//�ж�������ں����� ��ǩҳ�����Ӧ��URL��ַ
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
			//��ǰURL��ǰ׺
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
		//�ر�
		Close();
		return;
	}
	else if (sCtrlName == _T("minbtn"))
	{
		//��С��
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		return;
	}
	else if (sCtrlName == _T("maxbtn"))
	{
		//���
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		return;
	}
	else if (sCtrlName == _T("restorebtn"))
	{
		//���֮��Ļ�ԭ
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
		return;
	}
	else if (sCtrlName.Find(_T("tab-option-"), 0) != -1)
	{
		//����ҳǩ��Ĭ��ѡ�񽹵����½���ҳǩ
		std::wstring ctrlName(sCtrlName.GetData());
		SelectTab(ctrlName.substr(11));
	}
	else if (sCtrlName.Find(_T("tab-close-"), 0) != -1)
	{
		//�ر�ҳǩ
		std::wstring closeName(sCtrlName.GetData());
		CloseTab(closeName.substr(10));
	}
	else if (sCtrlName == _T("tool_back"))
	{
		auto bundle = m_currentBundle;
		if (bundle)
		{
			//���˹��ܣ�ֻ�ܽ���ǰҳURL���ӵ�ַ��ҳ����к��ˣ��¿�ҳ���޷�ʹ�ú��˹���
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
		//��ȡ��ǰҳ����ж��ں�����
		if (bundle)
		{
			//ǰ�����ܣ���������ƣ�ֻ���ڵ�ǰҳURL���ӵ�ַ��ҳ�����ǰ�����¿�ҳ���޷�ʹ��ǰ������
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
		//��ȡ��ǰҳ�����ͺ��ж��ں�
		if (bundle)
		{
			//ˢ��ҳ�湦��
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
		//��ȡ��ǰҳ����
		BookmarkWindow::GetInstance(m_hWnd)->ShowWindow(true, true);
		RECT rc;
		//���ص�ǰ���ڵı߿���γߴ磬�ߴ����������Ļ�������Ͻǵ���Ļ�������
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
		//��ȡ�������ǰ�ں˰汾
		auto bundle = m_currentBundle;
		if (bundle)
		{
			CButtonUI* pButtonUI = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"tool_switch"));
			CLabelUI* pLabelUI = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"SwitchLab"));
			CComboUI* pComboUI = static_cast<CComboUI*>(m_PaintManager.FindControl(L"ComboDemo1"));

			wstring location = m_pAddressUI->GetText().GetData();
			auto type = kernel_type(location);
			auto bundle = m_currentBundle;

			//�����CEF�ںˣ��л�ΪIE�ں�
			if (bundle->type == BROWSER_TYPE_CEF)
			{
				pComboUI->SetVisible(true);
				AddNewMIETab(location, type);

				pLabelUI->SetText(L"����");
				pButtonUI->SetToolTip(L"��ǰΪ����ģʽ,����л�Ϊ����ģʽ");
				pButtonUI->SetNormalImage(L"toolbar\\compati_normal.png");
				pButtonUI->SetHotImage(L"toolbar\\compati_hover.png");
				pButtonUI->SetPushedImage(L"toolbar\\compati_pushed.png");
			}
			//�����IE�ںˣ��л�ΪCEF
			else if (bundle->type == BROWSER_TYPE_MIE)
			{
				pComboUI->SetVisible(false);
				//CDuiString pDuiString = pComboUI->GetText();

				AddNewCEFTab(location);

				pLabelUI->SetText(L"����");
				pButtonUI->SetToolTip(L"��ǰΪ����ģʽ,����л�Ϊ����ģʽ");
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
		//��ǰ���ڵľ��
		auto bw = BookmarkMgrWindow::GetInstance(m_hWnd);
		bw->SetName(L"");
		bw->SetUrl(m_pAddressUI->GetText().GetData());
		bw->CenterWindow();
		bw->ShowWindow(true, true);
	}
	else if (sCtrlName == L"tool_clear")
	{
		//ɾ��CEF�����IE������
		ClearCEFCache();
		ClearIECache();
		auto manager = CefCookieManager::GetGlobalManager(nullptr);
		//ɾ��cookie����
		manager->DeleteCookies(L"", L"", nullptr);
	}
	//------
	else if (sCtrlName == _T("tool_download"))
	{
		if (m_bIsjsoninit) // ��ʼ��json
		{
			//�ӱ��ض�ȡҳ���ļ�����
			pushJsonToJS();// �Ѷ����������ؼ�¼���ݷ���ǰ��
			m_bIsjsoninit = false;
		}

		//��ʾ����ҳ��
		downloadBundle->tab->SetVisible(true); // ��ʾ
		SelectTab(downloadBundle->id); // �л�
		kp_isDownloadTabOpen = 1;
		//���ص�ַ������
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
	option->SetText(L"�±�ǩҳ");
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

//�½�IE�ں˵ı�ǩҳ
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

//�½�CEF�ں˵ı�ǩҳ
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

//�ر�ҳǩʱ�Ĵ���(���ֻʣ��һ����ǩҳ��ʱ�����رոñ�ǩ�費��Ҫ�˳������,��ǰ�Ĵ����ǹر�)
void CBaseWindow::CloseTab(std::wstring id)
{
	auto bundle = m_hashAll[id];
	if (bundle->type == BROWSER_TYPE_CEF)
	{

		if (bundle->browserid == downloadBundle->browserid) // ��������ع����ǩ
		{
			CHorizontalLayoutUI* tabStrip = static_cast<CHorizontalLayoutUI*>(bundle->tab->GetParent());
			CDuiPtrArray* options = m_PaintManager.FindSubControlsByClass(tabStrip, DUI_CTR_OPTION);
			if (options->GetSize() == 1) // ���ֻʣ��һ����ǩҳ��Ҳ��������tab��
			{
				tabStrip->Remove(bundle->tab, true); // ɾ������tab
				m_hashAll.erase(id);
			}
			else
			{
				downloadBundle->tab->SetVisible(false); // ���ڶ��ҳǩʱ���Զ���������tab
				kp_isDownloadTabOpen = 0;
				m_pAddressUI->SetVisible(true);
				SetAddrVisible(true);
			}

			// ����Ĵ���
			for (auto it : m_hashBookmark) // ���Ĳ��������
			{
				if (bundle == it.second)
				{
					//��������ʹ��earseɾ���ڵ㣬��һ��Ԫ�صĵ�ַ���أ��¸��ڵ��Զ���ǰ��(�ڴ����)
					m_hashBookmark.erase(it.first);
					break;
				}
			}
			//static_cast<CContainerUI*>(bundle->tab->GetParent())->Remove(bundle->tab, true);
			//m_hashAll.erase(id);
			if (m_currentBundle == bundle)
			{
				//FindSubControlByPoint ��ȡĳ�ؼ���ĳλ�õ��ӿؼ�����
				//FindSubControlByName ��ȡĳ�ؼ���ָ�����ƵĿؼ�����
				//FindSubControlByClass ��ȡĳ�ؼ���ָ�������Ŀؼ����� + ���ذ汾��ȡָ���������ҿؼ���
				//GetSubControlsByClass ��ȡ���ҿؼ���
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
			//�ر�ҳǩʱ��ɾ����ҳǩ������һҳǩ��ǰ��
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
	if (kp_isDownloadTabOpen == 1) // ���ر�ǩҳ��ʾ�������ߵ��˴������ر�ǩҳ��Ȼ���ڣ��ر����ر�ǩҳ�������Ѿ�����

	{
		// �����л�
		COptionUI* tab = reinterpret_cast<COptionUI*>(options->GetAt(options->GetSize() - 1));
		if (tab)
		{
			tab->Selected(true);
		}
	}
	else // ���ر�ǩҳ����
	{
		if (options->GetSize() > 1) // ��������tab���б��tab���л�����Ӧtab
		{
			COptionUI* tab = reinterpret_cast<COptionUI*>(options->GetAt(options->GetSize() - 1));
			if (tab)
			{
				tab->Selected(true);
			}
		}
		else { // ֻʣ����tab
			tabStrip->Remove(bundle->tab, true); // ɾ������tab
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
		//���������
		int nIndex = wParam;
		if (m_hashBookmark[nIndex])
		{
			//��ǩҳ�Ѿ�����ʱ��ѡ��ñ�ǩҳ
			SelectTab(m_hashBookmark[nIndex]->id);
		}
		else
		{
			//��ǩҳ������ʱ���½���ǩҳ
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
			if (bundle->browserid == downloadBundle->browserid) // ��������ع����ǩ,���ص�ַ������
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
			//�ж�������ں�������CEF����IE
			m_CEFBrowser->ShowPage(bundle->browserid);
			m_ContentView->SelectItem(m_CEFBrowser);
			//��ȡ�ñ�ǩҳ��URL
			m_pAddressUI->SetText(m_CEFBrowser->GetFinalURL(bundle->browserid).c_str());
		}
		else
		{
			m_MIEBrowser->ShowPage(bundle->browserid);
			m_ContentView->SelectItem(m_MIEBrowser);
			m_pAddressUI->SetText(m_MIEBrowser->GetFinalURL(bundle->browserid).c_str());
		}
		//����ǰҳ������Ϊ��ҳ��
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
	// �ļ���Ϣ����
	std::string strMsg = message->GetName();
	string::size_type idx;
	idx = strMsg.find("changestate");//�Ƿ��иı�״̬
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
	idx = strMsg.find("deleteDownloadFile");//�Ƿ�ɾ�������ص��ļ�
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
					m_downloaded_infor.erase(m_downloaded_infor.begin() + i);//ɾ����Ӧ��vector
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
		CTipMsgWnd::MessageBox(GetHWND(), L"��ʾ", L"ָ���ļ�������", MB_OK);
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

//�ж��ַ����Ƿ����ĳ�ַ���
//@params:str:����ַ���
//@params:contains_str:���������ַ���
//@return: false:δ���� true������
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
	//��ʼ������״̬��Ĭ����resume
	Downloadingstate filestate;
	filestate.Fileid = download_item->GetId();
	filestate.strstate = DownloadStateType[1];
	m_downloadingstate.push_back(filestate);

	//��ʾ����ҳ��
	downloadBundle->tab->SetVisible(true); // ��ʾ
	SelectTab(downloadBundle->id); // �л�
	kp_isDownloadTabOpen = 1;

	WCHAR sMyDocuPath[800] = { 0 };
	::SHGetSpecialFolderPathW(0, sMyDocuPath, CSIDL_PROFILE, 0);

	//������ظ����֣�˼�룺Ҫ���ص�ȥ����׺ �� �Ѵ��ڵ�ȥ�����źͺ�׺ ���бȽϣ�������ظ��ľ��� �Ѵ��ڵ��ļ������(i)��
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
		if (IsContainsStr(yicundemingzi, "(") && IsContainsStr(yicundemingzi, ")")) // �����������
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

	callback->Continue(sDownloadPath, false);//��һ�������������ļ�����ȫ·�������ļ���
											 //------
}



//------
wstring CBaseWindow::string2wstring(string str)
{
	wstring result;
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';//����ַ�����β
	result.append(buffer);
	delete[] buffer;//ɾ��������������ֵ 
	return result;
}

//��wstringת����string  
string CBaseWindow::wstring2string(wstring wstr)
{
	string result;
	//��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//���ֽڱ���ת���ɶ��ֽڱ���  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ  
	result.append(buffer);
	delete[] buffer;
	return result;
}

// �滻�ַ������ո��滻Ϊ "," ��ǰ����� ["��������� "]
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
			if (bIschange)//״̬�б仯��Ҫ�����Լ���¼�Ľṹ��
			{
				m_downloadingstate[j].strstate = str_downloadstate;
				return;//������״̬��ֵ֮����return
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

		////������ظ�����
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

		//�������Ѿ���ɵ�ʱ�򣬽������ļ�����Ϣ�浽vector������
		if (download_item->IsComplete())
		{
			////������ظ����ֵ������֮ǰ�ļ�¼
			//for (int a = 0; a < m_downloaded_infor.size(); a++)
			//{
			//	if (0 == strcmp(m_downloaded_infor[a].filename, strname.c_str()))
			//	{
			//		//m_downloaded_infor.erase(m_downloaded_infor.begin() + a);
			//		strname += "(1)";
			//		value["filename"] = strname;
			//	}
			//}
			//����µļ�¼
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
			m_downloaded_infor.push_back(finishfileinfor);//push������

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
//��ʽ��ʱ��
std::string CBaseWindow::FormatUTC2BJ(CefTime cef_time)
{
	std::stringstream str_stream;
	std::stringstream str_stream_zero;
	std::string  strformat = "";

	time_t gettime = cef_time.GetTimeT();
	struct tm *pFormatime;
	//time(&gettime); /*���time_t�ṹ��ʱ�䣬UTCʱ��*/
	pFormatime = localtime(&gettime); /*ת��Ϊstruct tm�ṹ�ĵ���ʱ��*/

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

//intתstring
std::string CBaseWindow::FormatINT2STR(int64 ndata)
{
	std::stringstream str_stream;
	std::string  str_format = "";

	str_stream << ndata;
	str_format = str_stream.str();
	str_stream.str("");
	return str_format;
}

//������ɵ�json����js
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

// IE��delegate���������߳��д���ģ���Ҫ������Ϣ�����̴߳���
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
	//ֱ�Ӱѽṹ����Ĳ���ȡ��������InternetSetCookieExW����Cookie
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
	//��ʾ/���ص�ַ������
	CVerticalLayoutUI *pAddr = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(L"tool_addr"));
	if (pAddr != nullptr)
	{
		bool bIsAddr = pAddr->IsVisible();
		if (bShow != bIsAddr)
			pAddr->SetVisible(bShow);
	}
	//����/����ǰ�������ˡ�ˢ��
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