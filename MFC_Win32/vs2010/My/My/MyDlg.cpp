
// MyDlg.cpp : ʵ���ļ�
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
int num=0;//�������
HTREEITEM SelectNode;

typedef struct
{//
	int ID;
	BYTE lparam[2048];

}COMMAND;

DWORD WINAPI CLisen(LPVOID lparam);
// CMyDlg �Ի���




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


// CMyDlg ��Ϣ�������

BOOL CMyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	m_TreeCtrl.InsertItem(_T("Զ�̵���"), 0, NULL, NULL, 0);

	WORD ver = MAKEWORD(2,2);
	WSAStartup(ver, &wsadata);
	server = INVALID_SOCKET;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyDlg::OnBnClickedButtonConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//char Buff[100];
	//UpdateData(TRUE);

	CString strServIp;
	GetDlgItemText(IDC_EDIT_ADDR, strServIp);
	//m_addr.GetBuffer();


	if(strServIp.IsEmpty())
	{
		MessageBox(_T("IP��ַΪ�գ�������IP��ַ"));
		return;

	}
	server = socket(AF_INET, SOCK_STREAM, 0);
	if(server == INVALID_SOCKET)
	{
		AfxMessageBox(_T("socket����ʧ��"));
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
		MessageBox(_T("���ӷ�����ʧ�ܣ�"));
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("���ӷ�����ʧ�ܣ�"));
		Sleep(1000);
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("������"));
		return;
	}
	GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("���ӷ������ɹ���"));
	char Buff[20];
	if( recv(server, Buff, sizeof(Buff), 0) == SOCKET_ERROR )
	{
		MessageBox(_T("������Ϣʧ�ܣ�"));
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("������Ϣʧ�ܣ�"));
		return;
	}
	if( strcmp(Buff, "Password") == 0 )
	{
		// ���������
		CPASSWD dlg;
ag:			dlg.DoModal();

		char password[20] = {0};

		USES_CONVERSION;
		strcpy_s(password, 16, T2A(PublicDir));
		//strcpy(password,(char*)PublicDir.LockBuffer());
		if( send(server, password, sizeof(password), 0) == SOCKET_ERROR)
		{
			MessageBox(_T("��������ʧ��"));
			closesocket(server);
			return;
		}
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("��������ɹ������ڵȴ���������֤"));
		if( recv(server, Buff, sizeof(Buff), 0) == SOCKET_ERROR )
		{
			MessageBox(_T("������Ϣʧ�ܣ�"));
			GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("������Ϣʧ�ܣ�"));
			return;
		}
		if( strcmp(Buff, "TRUE") == 0)
		{
			MessageBox(_T("����������ȷ"));
			GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("������ȷ��"));

			COMMAND command;
			memset( (char*)&command, 0, sizeof(command));//��ʼ��Ϊ��
			command.ID = GetDriver;//������Ϣ
			send(server, (char*)&command, sizeof(command), 0);
			CreateThread(NULL, 0, CLisen, this, NULL, NULL);


		}
		else if( strcmp(Buff, "FALSE") == 0)
		{
			MessageBox(_T("�����������"));
			GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("�������"));
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
			AfxMessageBox(_T("������Ϣ����"));
			continue;
		}
		else
		{
			switch(command.ID)
			{
			case GetDriver:
				OutputDebugString(_T("���������Ϣ\n"));
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
	OutputDebugString((LPCWSTR)buf);
	m_tree.InsertItem((LPCTSTR)buf, 1, 1, m_hRoot, 0);// ���������Ϣ
	m_tree.Expand(m_hRoot, TVE_EXPAND);//�������չ�������� 
	return 0;
}