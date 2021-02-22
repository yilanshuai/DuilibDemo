#include <windows.h>
#include <tchar.h>
#include "stdafx.h"

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
			else if (sCtrlName.Find(_T("tab-option-"), 0) != -1)
			{
				//增加页签后默认选择焦点在新建的页签
				std::wstring ctrlName(sCtrlName.GetData());
				//SelectTab(ctrlName.substr(11));
			}
			else if (sCtrlName.Find(_T("tab-close-"), 0) != -1)
			{
				//关闭页签
				std::wstring closeName(sCtrlName.GetData());
				//CloseTab(closeName.substr(10));
			}
			else if (sCtrlName == _T("explore"))
			{	
				CVerticalLayoutUI* sidevlayout = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("side_vlayout")));
				CHorizontalLayoutUI* tabstrip1 = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("Tabstrip1")));
				UINT tabindex = tabstrip1->GetCount();
				UINT sideindex = sidevlayout->GetCount();

				CTabLayoutUI* m_ContentView = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("Content")));
				CTabLayoutUI* m_ContentView1 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView1")));
				CTabLayoutUI* m_ContentTab = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab")));
				CTabLayoutUI* m_ContentTab1 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab1")));
				m_ContentView->SelectItem(m_ContentView1);
				m_ContentTab->SelectItem(m_ContentTab1);
				m_CurrentTabStrip = tabstrip1;
			
				
			}
			else if (sCtrlName == _T("personalinfo"))
			{
				CVerticalLayoutUI* sidevlayout = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("side_vlayout")));
				CHorizontalLayoutUI* tabstrip2 = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("Tabstrip2")));
				UINT tabindex = tabstrip2->GetCount();
				UINT sideindex = sidevlayout->GetCount();

				CTabLayoutUI* m_ContentView = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("Content")));
				CTabLayoutUI* m_ContentView2 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView2")));
				m_ContentView->SelectItem(m_ContentView2);
				CTabLayoutUI* m_ContentTab = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab")));
				CTabLayoutUI* m_ContentTab2 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab2")));
				m_ContentTab->SelectItem(m_ContentTab2);
				m_CurrentTabStrip = tabstrip2;


				

			}
			else if (sCtrlName == _T("modifypassword"))
			{
				CVerticalLayoutUI* sidevlayout = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("side_vlayout")));
				CHorizontalLayoutUI* tabstrip3 = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("Tabstrip3")));
				UINT tabindex = tabstrip3->GetCount();
				UINT sideindex = sidevlayout->GetCount();

				CTabLayoutUI* m_ContentView = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("Content")));
				CTabLayoutUI* m_ContentView3 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentView3")));
				m_ContentView->SelectItem(m_ContentView3);
				CTabLayoutUI* m_ContentTab = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab")));
				CTabLayoutUI* m_ContentTab3 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTab3")));
				m_ContentTab->SelectItem(m_ContentTab3);
				m_CurrentTabStrip = tabstrip3;

				
			}
			else if (sCtrlName == _T("Add1"))
			{
				UINT tabindex = m_CurrentTabStrip->GetCount();


				CContainerUI* pTab = new CContainerUI;
				/*std::wostringstream oss;
				oss << L"maxwidth=\"174\" name=\"tab-" << id << L"\"";
				pTab->SetAttributeList(oss.str().c_str());*/
				CDialogBuilder builder;
				builder.Create(_T("tab.xml"), (UINT)0, NULL, &m_PaintManager, pTab);
				m_CurrentTabStrip->AddAt(pTab, tabindex);

				COptionUI* option = static_cast<COptionUI*>(m_PaintManager.FindSubControlByClass(pTab, _T("Option"), 0));
				//option->SetName((std::wstring(L"tab-option-") + id).c_str());
				option->SetGroup(L"group-browser");
				option->SetText(L"新标签页");
				option->SetTextPadding({ 12, 0, 26, 0 });
				option->SetFont(0);
				//CButtonUI* close = static_cast<CButtonUI*>(m_PaintManager.FindSubControlByClass(pTab, _T("Button"), 0));
				//std::wostringstream closeAttributes;
				//closeAttributes << L"name=\"tab-close-" << id << L"\"";
				//close->SetAttributeList(closeAttributes.str().c_str());
				/*BrowserBundle* newBundle = new BrowserBundle();
				newBundle->closeButton = close;
				newBundle->tabButton = option;
				newBundle->tab = pTab;*/
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
private:
	CHorizontalLayoutUI* m_CurrentTabStrip;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DuiBrow"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();
	return 0;
}