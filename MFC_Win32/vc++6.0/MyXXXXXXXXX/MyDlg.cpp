// MyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "My.h"
#include "MyDlg.h"
#include "PASSWD.h"
#include "SYS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

WSADATA wsadata;
SOCKET server;
SOCKADDR_IN serveraddr;
int port = 12345;
CString PublicDir;
int num=0;//�������
HTREEITEM SelectNode;

typedef struct
{//
	int ID;
	BYTE lparam[2048];

}COMMAND;

DWORD WINAPI CLisen(LPVOID lparam);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About




class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_addr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_addr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_ADDR)->SetWindowText("127.0.0.1");// ��ʼ��edit��ֵ
	m_ImageList_tree.Create(16, 16, ILC_COLOR32, 20, 40 );// ����һ������
	HICON hIcon = NULL;

	hIcon = (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,16,16,NULL);
	m_ImageList_tree.Add(hIcon);
		hIcon = (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2),IMAGE_ICON,16,16,NULL);
	m_ImageList_tree.Add(hIcon);
		hIcon = (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON3),IMAGE_ICON,16,16,NULL);
	m_ImageList_tree.Add(hIcon);

	m_tree.SetImageList(&m_ImageList_tree,TVSIL_NORMAL);

	DWORD dwStyle = GetWindowLong(m_tree.m_hWnd, GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;//���ӷ��
	SetWindowLong(m_tree.m_hWnd, GWL_STYLE, dwStyle);
	m_hRoot = m_tree.InsertItem("Զ�̵���", 0, 0, 0, 0 );// ��������ؾ��

	WORD ver = MAKEWORD(2,2);
	WSAStartup(ver, &wsadata);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnOK() 
{
	// TODO: Add extra validation here
	char Buff[100];
	UpdateData(true);
	if( m_addr.IsEmpty())
	{
		MessageBox("IP��ַΪ�գ�������IP��ַ");
		return;

	}
	server = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.S_un.S_addr = inet_addr(m_addr.LockBuffer());
	if( connect(server, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) != 0)
	{
		MessageBox("���ӷ�����ʧ�ܣ�");
		GetDlgItem(IDC_WORK_START)->SetWindowText("���ӷ�����ʧ�ܣ�");
		Sleep(1000);
		GetDlgItem(IDC_WORK_START)->SetWindowText("������");
		return;
	}
	else
	{
		GetDlgItem(IDC_WORK_START)->SetWindowText("���ӷ������ɹ���");
		char Buff[20];
		if( recv(server, Buff, sizeof(Buff), 0) != SOCKET_ERROR )
		{
			if( strcmp(Buff, "Password") == 0 )
			{
				// ���������
				CPASSWD dlg;
ag:				dlg.DoModal();

				char password[100];
				strcpy(password,PublicDir.LockBuffer());
				if( send(server, password, sizeof(password), 0) == SOCKET_ERROR)
				{
					MessageBox("����ʧ��");
					closesocket(server);
					return;
				}
				else
				{
					GetDlgItem(IDC_WORK_START)->SetWindowText("��������ɹ������ڵȴ���������֤");
				}
				recv(server, Buff, sizeof(Buff), 0);
				if( strcmp(Buff, "TRUE") == 0)
				{
					MessageBox("����������ȷ");
					GetDlgItem(IDC_WORK_START)->SetWindowText("������ȷ��");
					
					COMMAND command;
					memset( (char*)&command, 0, sizeof(command));//��ʼ��Ϊ��
					command.ID = GetDriver;//������Ϣ
					send(server, (char*)&command, sizeof(command), 0);
					CreateThread(NULL, 0, CLisen, this, NULL, NULL);


				}
				if( strcmp(Buff, "FALSE") == 0)
				{
					MessageBox("�����������");
					GetDlgItem(IDC_WORK_START)->SetWindowText("�������");
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

				

			}
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
		if( recv(server, (char*)&command, sizeof(command), 0) == SOCKET_ERROR)
		{
			break;
		}
		else
		{
			switch(command.ID)
			{
			case GetDriver:
				dlg->GetDriverProc(command.lparam);
				break;
			}
		}

	
		

	}
	closesocket(server);
	return 0;
}

int CMyDlg::GetDriverProc(BYTE* DATE)
{// �Ѵ�����Ϣ��ʾ��������
	char buf[1024];
	strcpy(buf, (char*)DATE);
	m_tree.InsertItem(buf, 1, 1, m_hRoot, 0);// ���������Ϣ
	m_tree.Expand(m_hRoot, TVE_EXPAND);//�������չ�������� 
	return 0;
}



void CMyDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) //tree�пؼ���ѡ��
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	TVITEM item = pNMTreeView->itemNew;
	m_list.DeleteAllItems();// list��ɾ�����е���
	SelectNode = item.hItem;
	if(item.hItem == m_hRoot)
	{
		return;
	}
	HTREEITEM CurrentNode = item.hItem;
	while( m_tree.GetChildItem(CurrentNode) != NULL )
	{
		m_tree.DeleteItem(m_tree.GetChildItem(CurrentNode));

	}
	CString Temp;
	CString FullPath = "";
	while( CurrentNode != m_hRoot)
	{
		Temp = m_tree.GetItemText(CurrentNode);
		if(Temp.Right(1) != "\\")
		{
			Temp +="\\";
		}
		FullPath = Temp + FullPath;
		CurrentNode = m_tree.GetParentItem(CurrentNode);

	}
	COMMAND command;
	memset((char*)&command, 0, sizeof(command));
	command.ID = GetDirInfo;
	strcpy((char*)command.lparam, FullPath.LockBuffer());

	if( send(server, (char*)&command, sizeof(command), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("���ʹ�����Ϣʧ�ܣ�");
	}

	*pResult = 0;
}
