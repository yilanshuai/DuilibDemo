#include <windows.h>
#include <tchar.h>
#include "stdafx.h"
#include <sstream>
#include <stdio.h>
#include <list> 

#pragma once
#include "../DuiLib/UIlib.h"
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

class CDuiFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual CDuiString GetSkinFile() { return _T("DuiBrow.xml"); }
	virtual CDuiString GetSkinFolder() { return _T(""); }
	virtual void InitWindow()
	{
		CHorizontalLayoutUI* tabstrip1 = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("Tabstrip1")));
		m_CurrentTabStrip = tabstrip1;
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
			//else if (sCtrlName.Find(_T("tab-option-"), 0) != -1)
			//{
			//	//增加页签后默认选择焦点在新建的页签
			//	std::wstring ctrlName(sCtrlName.GetData());
			//	SelectTab(ctrlName.substr(11));
			//}
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
			}
			else if (sCtrlName == _T("NewTabButton"))
			{
				UINT tabindex = m_CurrentTabStrip->GetCount();
				CContainerUI* pTab = new CContainerUI;
				CDialogBuilder builder;
				builder.Create(_T("tab.xml"), (UINT)0, NULL, &m_PaintManager, pTab);
				m_CurrentTabStrip->AddAt(pTab, tabindex);

				COptionUI* option = static_cast<COptionUI*>(m_PaintManager.FindSubControlByClass(pTab, _T("Option"), 0));
				option->SetGroup(L"group-browser");
				option->SetText(L"新标签页");
				option->SetTextPadding({ 12, 0, 26, 0 });
				option->SetFont(0);

				CButtonUI* pbutton = static_cast<CButtonUI*>(m_PaintManager.FindSubControlByClass(pTab, _T("Button"), 0));

				std::wostringstream closeAttributes;
			
				std::wstring Tid = GetUniqueid();
				closeAttributes << L"name=\"tab-close-" << Tid << L"\"";
				pbutton->SetAttributeList(closeAttributes.str().c_str());

				BrowserBundle* bundle = new BrowserBundle(Tid);
				bundle->tab = pTab;
				bundleList.push_back(bundle);
			}
		}
	}

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
	BrowserBundle(std::wstring id) : id(id) {}
};

std::list <BrowserBundle*> bundleList;

private:
	CHorizontalLayoutUI* m_CurrentTabStrip;
		
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DuilibDemo"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();
	return 0;
}