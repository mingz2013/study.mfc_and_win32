
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_BUF_SIZE 4096


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg 对话框




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CClientDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(ThreadProc, this);
}
UINT __cdecl CClientDlg::ThreadProc( LPVOID pParam )
{
	ASSERT(pParam);
	CClientDlg *pThis = (CClientDlg*)pParam;
	pThis->WinSockInit();
	pThis->m_Socket = INVALID_SOCKET;
	pThis->m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(pThis->m_Socket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("新建socket失败"));
		goto _Error_End;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if(connect(pThis->m_Socket, (struct sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("连接失败，请重试"));
		goto _Error_End;
	}
	pThis->ShowMsg(_T("已连接到服务器..."));
	while(TRUE)
	{
		if(pThis->SOCKET_Select(pThis->m_Socket))
		{
			TCHAR szBuf[MAX_BUF_SIZE] = {0};
			int iRet = recv(pThis->m_Socket, (char*)szBuf, MAX_BUF_SIZE, 0);
			if(iRet > 0)
			{
				pThis->ShowMsg(szBuf);
			}
			else
			{
				pThis->ShowMsg(_T("服务器已断开，请重新连接"));
				break;
			}
		}
		Sleep(500);
	}

_Error_End:
	if(pThis->m_Socket != INVALID_SOCKET)
	{
		closesocket(pThis->m_Socket);
	}
	WSACleanup();
	return TRUE;
}


BOOL CClientDlg::WinSockInit()
{
	WSADATA data = {0};
	if(WSAStartup(MAKEWORD(2,2), &data))
	{
		return FALSE;
	}
	if(LOBYTE(data.wVersion) != 2 || HIBYTE(data.wVersion) != 2)
	{
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}


BOOL CClientDlg::SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut > 1000 ? 1000:nTimeOut;
	tv.tv_sec = 0;
	tv.tv_usec = nTimeOut;

	int iRet = 0;
	if(bRead)
	{
		iRet = select(0, &fdset, NULL, NULL, &tv);
	}
	else
	{
		iRet = select(0, NULL, &fdset, NULL, &tv);
	}

	if(iRet <= 0)
	{
		return FALSE;
	}
	else if(FD_ISSET(hSocket, &fdset))
	{
		return TRUE;
	}
	return FALSE;

}
void CClientDlg::ShowMsg(CString strMsg)
{
	CEdit *pEditShow = (CEdit*)GetDlgItem(IDC_EDIT_SHOW);
	ASSERT(pEditShow);
	pEditShow->SetSel(-1, -1);
	pEditShow->ReplaceSel(_T("Server:") + strMsg + _T("\r\n"));



}

void CClientDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
	ASSERT(m_Socket != INVALID_SOCKET);
	GetDlgItemText(IDC_EDIT_MSG, strText);
	if(!strText.IsEmpty() && SOCKET_Select(m_Socket, 100, FALSE))
	{
		send(m_Socket, (char*)strText.GetBuffer(), strText.GetLength()*sizeof(TCHAR), 0);
		SetDlgItemText(IDC_EDIT_MSG, _T(""));
	}
}
