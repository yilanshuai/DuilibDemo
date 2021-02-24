#pragma once
#   if defined(XBROWSER_EXPORTS)
#       if  defined(_MSC_VER)
#           define XBROWSER_API __declspec(dllexport)
#       else
#           define XBROWSER_API
#       endif
#   else
#       if defined(_MSC_VER)
#           define XBROWSER_API __declspec(dllimport)
#       else
#           define XBROWSER_API
#       endif
#   endif
#include "UIlib.h"
#include <functional>
#include <string>
#include <memory>

#define  POLICY_MASK_DISABLE_COPY 1
#define  POLICY_MASK_DISABLE_SAVE 2
#define  POLICY_MASK_DISABLE_DRAG 4
#define  POLICY_MASK_DISABLE_PRINT 8
#define  POLICY_MASK_DISABLE_VIEWSOURCE 16

// 国密需要的回调函数声明
typedef std::string(*PFSMProvideUICBSelectClientCert)(std::vector<std::string> clientCerts);
typedef std::string(*PFSMProvideUICBPinInput)(int* iFlag, int ulRetry);

// IPC代理
class IPCMsgDelegate
{
    public:
        // 命名管道被关掉
        virtual void OnPipeClosed(wstring pipename) = 0;
        // 接收到数据
        virtual void OnDataArrived(BYTE* lpBuffer, DWORD nNumberOfBytesToWrite) = 0;
};

class IPCServer;

namespace XBrowser
{
    class XBROWSER_API CmdLineUtil
    {
        public:
            // 解析命令行参数，如果是IE进程，返回true，否则返回false
            static bool ParseCmdLine();
            // 获取IE版本 IE11=0x2af9 IE10=0x2710  IE9=0x2328  IE8=0x1F40  IE7=0x1B58
            static DWORD GetCompatNum();
            // 获取命令行传过来的父窗口HWND
            static HWND GetParentHandle();
            // 获取当前的IE标签id
            static int GetBrowserId();
            // 获取当前的ie_process_version 6/7/8/9/10/11
            static int GetIEVer();
            static bool GetPopup();
            static int GetPopupLeft();
            static int GetPopupTop();
            static int GetPopupWidth();
            static int GetPopupHeight();
    };

    class XBROWSER_API IEUtil
    {
        public:
            static void SetForceProcessIEVersion(const std::string& IEVer);
            // 根据url获取IE版本的字符串形式
            static std::wstring GetIEVersionByUrl(std::wstring url);
            // 写注册表相关内容
            static void RegisterApp();
            // 设置过滤函数，根据url进行过滤，在BeforeNavigate的时候，如果过滤函数返回true,则被blocked, 进行其他操作，比如用cef打开
            static void SetBeforeNavUrlBlockFilter(std::function<bool(std::wstring)> filter);
            // 获取beforeNav过滤函数
            static std::function<bool(std::wstring)> GetBeforeNavUrlBlockFilter();
            // 设置过滤函数，根据url进行过滤，在新建标签页的时候，如果过滤函数返回true,则被blocked, 进行其他操作，比如用cef打开
            static void SetNewUrlBlockFilter(std::function<bool(std::wstring)> filter);
            // 获取新建标签页的过滤函数
            static std::function<bool(std::wstring)> GetNewUrlBlockFilter();

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
            static bool GetCanPrint();
            static bool GetCanViewSource();
            static bool GetShowAddressBar();
            static bool GetRecordVisit();

            static void SetCanCopy(bool bTrue);
            static void SetCanSave(bool bTrue);
            static void SetCanDrag(bool bTrue);
            static void SetCanPrint(bool bTrue);
            static void SetCanViewSource(bool bTrue);
            static void SetShowAddressBar(bool bTrue);
            static void SetRecordVisit(bool bTrue);

    };

    class MIEDelegate
    {
        public:
            // IE进程已创建
            virtual void OnIECreated(int browserid) = 0;
            // 标签页通过js调用关闭, browserid为新关闭的标签id
            virtual void OnIEClosed(int browserid) = 0;
			// IE窗口销毁后的通知
			virtual void OnIEDestroyed(int browserid) = 0;
            // IE的url改变,URL改变的时候，建议判断一下当前的标题，如果标题是about:blank的话，可以把当前URL当作标题
            virtual void OnSetIEURL(int browserid, const std::wstring& url) = 0;
            // IE的标题改变
            virtual void OnSetIETitle(int browserid, const std::wstring& title) = 0;
            // URL被阻塞
            virtual void OnUrlBlocked(int borwserid, const std::wstring& url) = 0;
            // 新标签页被创建, browserid为新创建的标签id
            virtual void OnNewViewCreated(int browserid) = 0;
            // 需要同步cookie
            virtual void OnNeedCookie(HWND hRenderWnd, wstring url, HANDLE hEvent) = 0;
            // 获取国密证书回调函数 函数调用在其他线程 回调函数请在主线程中处理
            virtual PFSMProvideUICBSelectClientCert GetSMCertCallback() = 0;
            // 获取输入PIN回调函数 函数调用在其他线程 回调函数请在主线程中处理
            virtual PFSMProvideUICBPinInput GetSMPinCallback() = 0;
        protected:
            virtual ~MIEDelegate() {}
    };

    // 启动IE进程,调用之前需要先调用 ParseCmdLine
    int XBROWSER_API StartIEProcess();

	struct MIEHashs
	{
		// 保存每个标签页的id及其对应的IPCServer
		unordered_map<int, shared_ptr<IPCServer>> m_IPCHashTable;
		// url的umap，保存每个标签页的id及其对应的url
		unordered_map<int, wstring> m_URLHashTable;
		// 保存每个标签页的id及其对应的窗口句柄
		unordered_map<int, HWND> m_hWndHashTable;
		unordered_map<int, wstring> m_externalDataHashTable;
		unordered_map<int, string> m_postBytesHashTable;
	};

    class XBROWSER_API CMIEBrowserUI : public DuiLib::CControlUI, public IPCMsgDelegate
    {
        public:
            explicit CMIEBrowserUI(HWND hParentWnd, MIEDelegate* delegate, bool sm_on = true);
            virtual ~CMIEBrowserUI();

            // ------------------以下为继承CControlUI的比较有用的接口 ------------------
            virtual LPCTSTR GetClass() const;
            virtual LPVOID GetInterface(LPCTSTR pstrName);
            virtual void SetPos(RECT rc, bool bNeedInvalidate = true);
            virtual void SetVisible(bool bVisible = true);

            // 继承IPCMsgDelegate的方法
            virtual void OnDataArrived(BYTE* lpBuffer, DWORD nNumberOfBytesToWrite);
            virtual void OnPipeClosed(wstring pipename);

            // 新建标签页，返回标签页id，默认不忽略证书错误，可以传入参数忽略证书错误
            // 国密网址无需设置，默认忽略证书错误
			int NewPage(wstring url, wstring forceIEVer = L"", 
				bool bPopup = false, int nPopupLeft = 0, int nPopupTop = 0, 
				int nPopupWidth = 800, int nPopupHeight = 600);
			void SetExternalData(int browserid, std::wstring externalData);
			void SetPostBytes(int browserid, std::string postBytes);
            // 显示标签页，传入标签页id
            void ShowPage(int nBrowserId);
            //删除标签页，传入标签页id
            void DelPage(int nBrowserId);

            // 刷新页面
            void ReLoad(int nBrowserId);
            // 停止页面刷新
            void StopLoad(int nBrowserId);
            // 某个标签页载入url
            void LoadURL(int nBrowserId, wstring url);
            // 获取该标签页的url
            std::wstring GetFinalURL(int nBrowserId);

            // 是否能前进|后退及前进后退功能
            BOOL CanGoForward(int nBrowserId);
            void GoForward(int nBrowserId);
            BOOL CanGoBack(int nBrowserId);
            void GoBack(int nBrowserId);
            void SetCookie(COPYDATASTRUCT* pCopyDataStruct);
			void SetTrustNumber(wstring trustNumber);

        protected:
            // 父窗口的句柄
            HWND m_hParentWnd;
            // 当前显示的标签id
            int m_nSelectedId;
        private:
			MIEHashs* m_hashs;
            MIEDelegate* m_MIEDelegate;
            int m_nSMListenPort;
			bool m_sm_on;
			wstring m_trustNumber;
    };
}
