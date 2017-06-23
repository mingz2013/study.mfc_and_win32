
// MyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "My.h"
#include "MyDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "PASSWD.h"
#include "SYS.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


WSADATA wsadata;
SOCKET server;
SOCKADDR_IN serveraddr;
int port = 12345;
CString PublicDir;
int num=0;//密码次数
HTREEITEM SelectNode;

typedef struct
{//
	int ID;
	BYTE lparam[2048];

}COMMAND;

DWORD WINAPI CLisen(LPVOID lparam);
// CMyDlg 对话框




CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDlg::IDD, pParent)
	//,// m_addr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_Edit = _T("");
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_TreeCtrl);
	//  DDX_Control(pDX, IDC_EDIT_ADDR, m_Edit);
	//DDX_Text(pDX, IDC_EDIT_ADDR, m_Edit);
	//  DDX_Text(pDX, IDC_EDIT_ADDR, m_addr);
	//  DDX_Control(pDX, IDC_EDIT_ADDR, m_Edit);
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONN, &CMyDlg::OnBnClickedButtonConn)
END_MESSAGE_MAP()


// CMyDlg 消息处理程序

BOOL CMyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT_ADDR)->SetWindowTextW(_T("127.0.0.1"));

	m_ImageList_Tree.Create(16, 16, ILC_COLOR32, 20, 40);
	HICON hIcon = NULL;
	hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, NULL);
	m_ImageList_Tree.Add(hIcon);
	m_TreeCtrl.SetImageList(&m_ImageList_Tree, TVSIL_NORMAL);
	hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, NULL);
	m_ImageList_Tree.Add(hIcon);
	m_TreeCtrl.SetImageList(&m_ImageList_Tree, TVSIL_NORMAL);
	hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 16, 16, NULL);
	m_ImageList_Tree.Add(hIcon);
	m_TreeCtrl.SetImageList(&m_ImageList_Tree, TVSIL_NORMAL);

	m_TreeCtrl.InsertItem(_T("远程电脑"), 0, NULL, NULL, 0);

	WORD ver = MAKEWORD(2,2);
	WSAStartup(ver, &wsadata);
	server = INVALID_SOCKET;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyDlg::OnPaint()
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
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyDlg::OnBnClickedButtonConn()
{
	// TODO: 在此添加控件通知处理程序代码
	//char Buff[100];
	//UpdateData(TRUE);

	CString strServIp;
	GetDlgItemText(IDC_EDIT_ADDR, strServIp);
	//m_addr.GetBuffer();


	if(strServIp.IsEmpty())
	{
		MessageBox(_T("IP地址为空，请输入IP地址"));
		return;

	}
	server = socket(AF_INET, SOCK_STREAM, 0);
	if(server == INVALID_SOCKET)
	{
		AfxMessageBox(_T("socket建立失败"));
		return ;
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	char szIpAddr[16] = {0};
	USES_CONVERSION;
	strcpy_s(szIpAddr, 16, T2A(strServIp));
	serveraddr.sin_addr.S_un.S_addr = inet_addr(szIpAddr);/*("127.0.0.1");//((char*)m_addr.LockBuffer());*/
	OutputDebugString((LPCWSTR)szIpAddr);
	if( connect(server, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
	{
		MessageBox(_T("连接服务器失败！"));
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("连接服务器失败！"));
		Sleep(1000);
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("无连接"));
		return;
	}
	GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("连接服务器成功！"));
	char Buff[20];
	if( recv(server, Buff, sizeof(Buff), 0) == SOCKET_ERROR )
	{
		MessageBox(_T("接收信息失败！"));
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("接收信息失败！"));
		return;
	}
	if( strcmp(Buff, "Password") == 0 )
	{
		// 弹出密码框
		CPASSWD dlg;
ag:			dlg.DoModal();

		char password[20] = {0};

		USES_CONVERSION;
		strcpy_s(password, 16, T2A(PublicDir));
		//strcpy(password,(char*)PublicDir.LockBuffer());
		if( send(server, password, sizeof(password), 0) == SOCKET_ERROR)
		{
			MessageBox(_T("发送密码失败"));
			closesocket(server);
			return;
		}
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("发送密码成功，正在等待服务器验证"));
		if( recv(server, Buff, sizeof(Buff), 0) == SOCKET_ERROR )
		{
			MessageBox(_T("接收信息失败！"));
			GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("接收信息失败！"));
			return;
		}
		if( strcmp(Buff, "TRUE") == 0)
		{
			MessageBox(_T("输入密码正确"));
			GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("密码正确！"));

			COMMAND command;
			memset( (char*)&command, 0, sizeof(command));//初始化为零
			command.ID = GetDriver;//磁盘信息
			send(server, (char*)&command, sizeof(command), 0);
			CreateThread(NULL, 0, CLisen, this, NULL, NULL);


		}
		else if( strcmp(Buff, "FALSE") == 0)
		{
			MessageBox(_T("输入密码错误"));
			GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("密码错误！"));
			num++;
			if(num < 3)
			{
				goto ag;
			}
			else
			{
				OnCancel();
			}

		}
		else
		{
		}
	}



	//	CDialog::OnOK();
	//	closesocket(server);
	//	WSACleanup();
	;
}
void CMyDlg::SetPubDir(CString path)
{
	PublicDir = path;
}

DWORD WINAPI CLisen(LPVOID lparam)
{
	CMyDlg* dlg = (CMyDlg*)lparam;
	COMMAND command;
	memset((char*)&command, 0, sizeof(command));

	while(1)
	{
		memset((char*)&command, 0, sizeof(command));
		//char buff[1024] = {0};
		if( recv(server, (char*)&command, sizeof(command), 0) == SOCKET_ERROR)
		{
			//break;
			AfxMessageBox(_T("接收消息错误"));
			continue;
		}
		else
		{
			switch(command.ID)
			{
			case GetDriver:
				OutputDebugString(_T("插入磁盘信息\n"));
				dlg->GetDriverProc(command.lparam);
				break;
			}
		}
	}
	closesocket(server);
	return 0;
}

int CMyDlg::GetDriverProc(BYTE* DATE)
{// 把磁盘信息显示在树表中
	char buf[1024];
	strcpy(buf, (char*)DATE);
	OutputDebugString((LPCWSTR)buf);
	m_tree.InsertItem((LPCTSTR)buf, 1, 1, m_hRoot, 0);// 插入磁盘信息
	m_tree.Expand(m_hRoot, TVE_EXPAND);//设置项的展开和收缩 
	return 0;
}