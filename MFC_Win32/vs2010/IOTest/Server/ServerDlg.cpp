
// ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_BUF_SIZE 4096
#define SOMAXCONN 5

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CServerDlg �Ի���




CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CServerDlg::OnBnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CServerDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CServerDlg ��Ϣ�������

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::OnBnClickedButtonListen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxBeginThread(ThreadProc, this);
}


void CServerDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText;
	ASSERT(m_SockClient != INVALID_SOCKET);
	GetDlgItemText(IDC_EDIT_MSG, strText);
	if(!strText.IsEmpty() && SOCKET_Select(m_SockClient, 100, FALSE))
	{
		send(m_SockClient, (char*)strText.GetBuffer(), strText.GetLength()*sizeof(TCHAR), 0);
		SetDlgItemText(IDC_EDIT_MSG, _T(""));
	}
}

UINT __cdecl CServerDlg::ThreadProc( LPVOID pParam )
{
	ASSERT(pParam);
	sockaddr_in clientAddr = {0};
	CServerDlg *pThis = (CServerDlg*)pParam;
	pThis->WinSockInit();
	pThis->m_SockListen = INVALID_SOCKET;
	pThis->m_SockListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(pThis->m_SockListen == INVALID_SOCKET)
	{
		AfxMessageBox(_T("�½�socketʧ�ܣ�"));
		goto _Error_End;
	}
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_port = htons(1234);
	service.sin_addr.S_un.S_addr = INADDR_ANY;
	if(bind(pThis->m_SockListen, (struct sockaddr*)&service, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�󶨶˿�ʧ�ܣ�"));
		goto _Error_End;
	}

	if(listen(pThis->m_SockListen, SOMAXCONN) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("�����˿�ʧ�ܣ�"));
		goto _Error_End;
	}
	pThis->ShowMsg(_T("�������ɹ��������ȴ��ͻ�����...\r\n"));
	int iLen = sizeof(sockaddr_in);
	pThis->m_SockClient = accept(pThis->m_SockListen, (struct sockaddr*)&clientAddr, &iLen);
	if(pThis->m_SockClient == INVALID_SOCKET)
	{
		goto _Error_End;
	}
	pThis->ShowMsg(_T("�пͻ���������...\r\n"));
	while(TRUE)
	{
		if(pThis->SOCKET_Select(pThis->m_SockClient))
		{
			TCHAR szBuf[MAX_BUF_SIZE] = {0};
			int iRet = recv(pThis->m_SockClient, (char*)szBuf, MAX_BUF_SIZE, 0);
			if(iRet > 0)
			{

				pThis->ShowMsg(szBuf);
			}
			else
			{
				pThis->ShowMsg(_T("�ͻ��������ߣ������¿����������ȴ�����\r\n"));
				break;
			}
		}
		Sleep(500);
	}


_Error_End:
	if(pThis->m_SockListen != INVALID_SOCKET)
	{
		closesocket(pThis->m_SockListen);
	}
	WSACleanup();
	return TRUE;
}

BOOL CServerDlg::WinSockInit()
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

void CServerDlg::ShowMsg(CString strMsg)
{
	CEdit *pEditShow = (CEdit*)GetDlgItem(IDC_EDIT_SHOW);
	ASSERT(pEditShow);
	pEditShow->SetSel(-1, -1);
	pEditShow->ReplaceSel(_T("Client:") + strMsg + _T("\r\n"));



}

BOOL CServerDlg::SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
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