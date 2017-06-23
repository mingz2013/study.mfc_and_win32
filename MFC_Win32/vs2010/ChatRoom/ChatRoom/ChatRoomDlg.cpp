
// ChatRoomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "ChatRoomDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Inc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatRoomDlg 对话框




CChatRoomDlg::CChatRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatRoomDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bShowAll = FALSE;
	m_ListenSock = INVALID_SOCKET;
}

void CChatRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHATSHOW, m_EditChatShow);
}

BEGIN_MESSAGE_MAP(CChatRoomDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_RADIO_SERVER, &CChatRoomDlg::OnBnClickedRadioServer)
	ON_BN_CLICKED(IDC_BUTTON_NET, &CChatRoomDlg::OnBnClickedButtonNet)
	ON_BN_CLICKED(IDC_BUTTON_STARTSEV, &CChatRoomDlg::OnBnClickedButtonStartsev)
	ON_BN_CLICKED(IDC_RADIO_CLIENT, &CChatRoomDlg::OnBnClickedRadioClient)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatRoomDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CChatRoomDlg::OnBnClickedButtonConnect)
	ON_EN_CHANGE(IDC_EDIT_CHATMSG, &CChatRoomDlg::OnEnChangeEditChatmsg)
	ON_BN_CLICKED(IDC_BUTTON_STOPCON, &CChatRoomDlg::OnBnClickedButtonStopcon)
	ON_BN_CLICKED(IDC_BUTTON_STOPSEV, &CChatRoomDlg::OnBnClickedButtonStopsev)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CChatRoomDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_MORE, &CChatRoomDlg::OnBnClickedButtonMore)
	ON_COMMAND(ID_MENU_TRAYICON, &CChatRoomDlg::OnMenuTrayicon)

	ON_MESSAGE(WM_TRAYICON_MSG, OnTrayCallBackMsg)// 将函数和消息关联起来
	ON_COMMAND(ID_MENU_SHOW, &CChatRoomDlg::OnMenuShow)
	ON_COMMAND(ID_MENU_EXIT, &CChatRoomDlg::OnMenuExit)
END_MESSAGE_MAP()


// CChatRoomDlg 消息处理程序

BOOL CChatRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	DlgAllInit();
	ExtendDlg(FALSE);
	bShowAll = FALSE;
	m_bIsServer = -1;
	m_ListenSock = INVALID_SOCKET;
	m_ConnectSock = INVALID_SOCKET;
	m_hListenThread = NULL;
	m_hConnectThread = NULL;
	bShutDown = FALSE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatRoomDlg::OnPaint()
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
HCURSOR CChatRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatRoomDlg::DlgAllInit()
{// 初始化


	// 禁用控件
	EnableWindow(IDC_BUTTON_SEND, FALSE);

	EnableWindow(IDC_BUTTON_STOPCON,FALSE);
	EnableWindow(IDC_STATIC,FALSE);
	EnableWindow(IDC_EDIT_LOCALPORT,FALSE);
	EnableWindow(IDC_BUTTON_STARTSEV,FALSE);
	EnableWindow(IDC_BUTTON_STOPSEV,FALSE);
	EnableWindow(IDC_BUTTON_SEND,FALSE);


	CheckRadioButton(IDC_RADIO_CLIENT,IDC_RADIO_CLIENT,IDC_RADIO_CLIENT);// 单选框初始值
	SetDlgItemText(IDC_IPADDRESS, _T("127.0.0.1"));
	SetDlgItemText(IDC_EDIT_SERVERPORT, _T("10000"));
	SetDlgItemText(IDC_EDIT_LOCALPORT, _T("10000"));

}


BOOL CChatRoomDlg::EnableWindow(UINT uID, BOOL bEnable )
{
	// 对控件禁止或启用
	//return GetDlgItem(uID)->EnableWindow(bEnable);
	return ::EnableWindow(GetDlgItem(uID)->GetSafeHwnd(),bEnable);
}

void CChatRoomDlg::OnBnClickedRadioServer()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	if(FALSE == m_bIsServer)
	{
		int iRet = MessageBox(_T("您是聊天室的客户端，是否退出？"),_T("提示"),MB_OKCANCEL);
		if(IDOK == iRet)
		{
			StopClient();
		}
		else
		{
			CheckRadioButton(IDC_RADIO_CLIENT, IDC_RADIO_SERVER, IDC_RADIO_CLIENT);
		}
	}
	if(IDOK == iRet || -1 == m_bIsServer)
	{
		// 禁用控件，服务端被选中
		EnableWindow(IDC_STATIC,FALSE);
		EnableWindow(IDC_IPADDRESS,FALSE);
		EnableWindow(IDC_STATIC,FALSE);
		EnableWindow(IDC_EDIT_SERVERPORT,FALSE);
		EnableWindow(IDC_BUTTON_CONNECT,FALSE);
		EnableWindow(IDC_BUTTON_STOPCON,FALSE);

		// 开启控件

		EnableWindow(IDC_STATIC,TRUE);
		EnableWindow(IDC_EDIT_LOCALPORT,TRUE);
		EnableWindow(IDC_BUTTON_STARTSEV,TRUE);
		//EnableWindow(IDC_BUTTON_STOPSEV,TRUE);
	}

}


void CChatRoomDlg::ExtendDlg(BOOL bShow)
{
	static CRect m_DlgRectLarge(0,0,0,0);
	static CRect m_DlgRectSmall(0,0,0,0);

	static CRect m_GroupRectLarge(0,0,0,0);
	static CRect m_GroupRectSmall(0,0,0,0);

	if(m_DlgRectLarge.IsRectNull())//第一次调用/
	{
		GetWindowRect(&m_DlgRectLarge);
	    m_DlgRectSmall = m_DlgRectLarge;
	    m_DlgRectSmall.right -= 285;

		::GetWindowRect(GetDlgItem(IDCANCEL)->GetSafeHwnd(), m_GroupRectLarge);
		m_GroupRectSmall = m_GroupRectLarge;
	    m_GroupRectSmall.right -= 275;
	}

	

	if(bShow)
	{
		bShowAll = TRUE;
		SetWindowPos(NULL, m_DlgRectLarge.left, m_DlgRectLarge.top, m_DlgRectLarge.Width(), m_DlgRectLarge.Height(), SWP_NOZORDER|SWP_NOMOVE);
		::SetWindowPos(GetDlgItem(IDCANCEL)->GetSafeHwnd(),NULL,  m_GroupRectLarge.left, m_GroupRectLarge.top, m_GroupRectLarge.Width(), m_GroupRectLarge.Height(),SWP_NOZORDER|SWP_NOMOVE); 
	}
	else
	{
		bShowAll = FALSE;
		SetWindowPos(NULL, m_DlgRectSmall.left, m_DlgRectSmall.top, m_DlgRectSmall.Width(), m_DlgRectSmall.Height(), SWP_NOZORDER|SWP_NOMOVE);
		::SetWindowPos(GetDlgItem(IDCANCEL)->GetSafeHwnd(),NULL,  m_GroupRectSmall.left, m_GroupRectSmall.top, m_GroupRectSmall.Width(), m_GroupRectSmall.Height(),SWP_NOZORDER|SWP_NOMOVE);
	}
}

void CChatRoomDlg::OnBnClickedButtonNet()
{
	// TODO: 在此添加控件通知处理程序代码
	if(bShowAll)
	{
			ExtendDlg(FALSE);
	}
	else
	{
		ExtendDlg(TRUE);
	}
}


void CChatRoomDlg::OnBnClickedButtonStartsev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_hListenThread = CreateThread(NULL, 0, ListenThreadFunc, this, 0, NULL);

	/*
	
	*/
}

void CChatRoomDlg::OnBnClickedRadioClient()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	if(TRUE == m_bIsServer)
	{
		int iRet = MessageBox(_T("您是聊天室的服务端，是否退出？"),_T("提示"),MB_OKCANCEL);
		if(IDOK == iRet)
		{
			StopServer();
		}
		else
		{
			CheckRadioButton(IDC_RADIO_CLIENT, IDC_RADIO_SERVER, IDC_RADIO_SERVER);
		}
	}
	if(IDOK == iRet || -1 == m_bIsServer)
	{
		// 开启控件，客户端被选中
		EnableWindow(IDC_STATIC,TRUE);
		EnableWindow(IDC_IPADDRESS,TRUE);
		EnableWindow(IDC_STATIC,TRUE);
		EnableWindow(IDC_EDIT_SERVERPORT,TRUE);
		EnableWindow(IDC_BUTTON_CONNECT,TRUE);
		//EnableWindow(IDC_BUTTON_STOPCON,TRUE);

		// 禁用控件

		EnableWindow(IDC_STATIC,FALSE);
		EnableWindow(IDC_EDIT_LOCALPORT,FALSE);
		EnableWindow(IDC_BUTTON_STARTSEV,FALSE);
		EnableWindow(IDC_BUTTON_STOPSEV,FALSE);
	}
}




void CChatRoomDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strMsg;
	GetDlgItemText(IDC_EDIT_CHATMSG, strMsg);
	if(TRUE == m_bIsServer)
	{
		strMsg = _T("服务器：〉") + strMsg;
		ShowMsg(strMsg);
		SendClientsMsg(strMsg);
	}
	else if(FALSE == m_bIsServer)
	{
		CString strTmp = _T("本地客户端：〉") + strMsg;
		ShowMsg(strTmp);
		OutputDebugString((LPWSTR)strMsg.GetBuffer());
		int iSend = send(m_ConnectSock, (char*)strMsg.GetBuffer(), strMsg.GetLength()*sizeof(TCHAR), 0);
		
	}
	else
	{
		ShowMsg(_T("系统消息： 请先进行网络设置！"));
	}
	strMsg.ReleaseBuffer();
	SetDlgItemText(IDC_EDIT_CHATMSG, _T(""));
}


void CChatRoomDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	m_hConnectThread = CreateThread(NULL, 0, ConnectThreadFunc, this, 0, NULL);
}


void CChatRoomDlg::OnEnChangeEditChatmsg()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strMsg;
	GetDlgItemText(IDC_EDIT_CHATMSG, strMsg);
	if(strMsg.IsEmpty())
	{
		EnableWindow(IDC_BUTTON_SEND, FALSE);
	}
	else
	{
		EnableWindow(IDC_BUTTON_SEND);
	}
}


void CChatRoomDlg::OnBnClickedButtonStopcon()
{
	// TODO: 在此添加控件通知处理程序代码
	StopClient();
}


void CChatRoomDlg::OnBnClickedButtonStopsev()
{
	// TODO: 在此添加控件通知处理程序代码
	StopServer();
}


void CChatRoomDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	if(TRUE == m_bIsServer)
	{
		StopServer();
	}
	else if(FALSE == m_bIsServer)
	{
		StopClient();
	}
	OnCancel();
}


void CChatRoomDlg::OnBnClickedButtonMore()
{
	// TODO: 在此添加控件通知处理程序代码
	// 弹出菜单
	CPoint pt;// 一个 点 类 对象
	CRect mRect;// 矩形类
	CMenu mMenu, *pMenu = NULL;// 菜单对象
	GetDlgItem(IDC_BUTTON_MORE)->GetWindowRect(&mRect);// 取得 更多功能 按钮的矩形
	pt = mRect.BottomRight();// 取得右下角的点
	pt.y = mRect.top + 10;
	mMenu.LoadMenu(IDR_MENU1);// 关联一个菜单资源
	pMenu = mMenu.GetSubMenu(0);// 因为顶层菜单不显示，指向子菜单项
	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);// 弹出菜单

}
BOOL CChatRoomDlg::TrayMyIcon(BOOL bAdd)
{ // 任务栏托盘函数************************
	BOOL bRet = FALSE;
	NOTIFYICONDATA tnd;// 结构体
	tnd.cbSize = sizeof(NOTIFYICONDATA);// 大小
	//tnd.hWnd = m_hWnd; // 本程序窗口的句柄，或者GetSafeHwnd();返回本程序句柄
	tnd.hWnd = GetSafeHwnd();
	tnd.uID = IDR_MAINFRAME;// 图标的ID
	if(TRUE == bAdd)// 添加还是删除托盘图标
	{
		tnd.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;// 开启可用的功能
		tnd.uCallbackMessage = WM_TRAYICON_MSG;// 回调的消息,发给窗口的
		tnd.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));// 哪一个图标
		_tcscpy_s(tnd.szTip, sizeof(tnd.szTip), _T("ChatRoom"));// 鼠标放上去时显示的文本提示
		ShowWindow(SW_MINIMIZE);// 最小化窗口，这句可不用
		ShowWindow(SW_HIDE);// 隐藏窗口
		bRet = Shell_NotifyIcon(NIM_ADD, &tnd);// 最主要的函数，添加托盘图标
	}
	else
	{
		ShowWindow(SW_SHOWNA);// 显示主窗口
		SetForegroundWindow();// 设置成前景窗口
		bRet = Shell_NotifyIcon(NIM_DELETE, &tnd);// 删除托盘图标
	}
	return bRet;
}



void CChatRoomDlg::OnMenuTrayicon()
{
	// TODO: 在此添加命令处理程序代码
	TrayMyIcon();
}

LRESULT CChatRoomDlg::OnTrayCallBackMsg(WPARAM wparam, LPARAM lparam)
{//自定义消息 WM_TRAYICON_MSG 的消息响应函数
	switch(lparam)// lparam 保存消息号
	{
	case WM_RBUTTONUP:// 鼠标右键弹起
		{
			CPoint pt;// 一个 点 类 对象
			CMenu mMenu, *pMenu = NULL;
			mMenu.LoadMenu(IDR_MENU2);// 关联一个菜单资源
			pMenu = mMenu.GetSubMenu(0);// 因为顶层菜单不显示，指向子菜单项
			GetCursorPos(&pt);
			SetForegroundWindow();// 前景窗口
			pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);// 弹出菜单
			break;
		}
	case WM_LBUTTONDBLCLK:// 左键双击
		{
			ShowWindow(SW_RESTORE);
			SetForegroundWindow();
			TrayMyIcon(FALSE);// 删除图标
			break;
		}
	default:break;
	}
	return FALSE;
}


void CChatRoomDlg::OnMenuShow()
{
	// TODO: 在此添加命令处理程序代码
	ShowWindow(SW_RESTORE);
	TrayMyIcon(FALSE);// 删除图标
}


void CChatRoomDlg::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码
	TrayMyIcon(FALSE);// 删除图标
	OnBnClickedButtonClose();// 退出程序
}
