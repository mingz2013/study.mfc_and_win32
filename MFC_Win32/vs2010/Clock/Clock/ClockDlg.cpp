
// ClockDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Clock.h"
#include "ClockDlg.h"
#include "afxdialogex.h"
//#include <MMSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





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


// CClockDlg 对话框




CClockDlg::CClockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditCtrl);
}

BEGIN_MESSAGE_MAP(CClockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()



void CALLBACK CClockDlg::TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)// 时钟函数
{
	SYSTEMTIME lpLocalTime;
	char chTimeBuf[256];
	//memset((void*)lpLocalTime, 0, sizeof(lpLocalTime));
	memset(chTimeBuf, 0, sizeof(chTimeBuf));
	GetLocalTime(&lpLocalTime);
	wsprintf((LPWSTR)chTimeBuf, _T("%04d-%02d-%02d %02d:%02d:%02d 周%d\r\n"),
												lpLocalTime.wYear,
												lpLocalTime.wMonth,
												lpLocalTime.wDay,
												lpLocalTime.wHour,
												lpLocalTime.wMinute,
												lpLocalTime.wSecond,
												lpLocalTime.wDayOfWeek);
	//Edit.SetWindowTextW((LPCTSTR)chTimeBuf);
	//SetDlgItemText(AfxGetInstanceHandle(), IDC_EDIT1, (LPCWSTR)chTimeBuf);
	//SendMessage();
	//CClockDlg
	//dlg.m_EditCtrl.SetWindowTextW((LPCTSTR)chTimeBuf);
	//GetDlgItem(IDC_EDIT1)->SetWindowTextW(_T("127.0.0.1"));

	
	OutputDebugString((LPCWSTR)chTimeBuf);
	//AfxMessageBox((LPCTSTR)chTimeBuf);
	
	
}
// CClockDlg 消息处理程序

BOOL CClockDlg::OnInitDialog()
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
	//PlaySound(_T("IDR_WAVE1"),(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), SND_RESOURCE|SND_ASYNC|SND_LOOP);
	
	SetTimer(NULL, 1000, TimerProc);// 设置时钟


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}




void CClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClockDlg::OnPaint()
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
HCURSOR CClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

