
// ClientDlg.cpp : ʵ���ļ�
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


// CClientDlg �Ի���




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


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnBnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox(_T("�½�socketʧ��"));
		goto _Error_End;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if(connect(pThis->m_Socket, (struct sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ʧ�ܣ�������"));
		goto _Error_End;
	}
	pThis->ShowMsg(_T("�����ӵ�������..."));
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
				pThis->ShowMsg(_T("�������ѶϿ�������������"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText;
	ASSERT(m_Socket != INVALID_SOCKET);
	GetDlgItemText(IDC_EDIT_MSG, strText);
	if(!strText.IsEmpty() && SOCKET_Select(m_Socket, 100, FALSE))
	{
		send(m_Socket, (char*)strText.GetBuffer(), strText.GetLength()*sizeof(TCHAR), 0);
		SetDlgItemText(IDC_EDIT_MSG, _T(""));
	}
}
