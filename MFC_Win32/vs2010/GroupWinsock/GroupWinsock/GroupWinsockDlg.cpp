
// GroupWinsockDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GroupWinsock.h"
#include "GroupWinsockDlg.h"
#include "afxdialogex.h"
#define MAX_BUF_SIZE 1024
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CGroupWinsockDlg �Ի���




CGroupWinsockDlg::CGroupWinsockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGroupWinsockDlg::IDD, pParent)
	//, m_pMainWnd(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGroupWinsockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_GROUPIP, m_GroupIP);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_Show);
}

BEGIN_MESSAGE_MAP(CGroupWinsockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CGroupWinsockDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CGroupWinsockDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CGroupWinsockDlg ��Ϣ�������

BOOL CGroupWinsockDlg::OnInitDialog()
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
	m_GroupIP.SetWindowTextW(_T("234.5.6.7"));
	SetDlgItemInt(IDC_EDIT_PORT, 10000);
	int len = sizeof(struct sockaddr_in);
	m_hThread = NULL;


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGroupWinsockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGroupWinsockDlg::OnPaint()
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
HCURSOR CGroupWinsockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGroupWinsockDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	
m_hThread = CreateThread(NULL, 0, ClientThreadProc, this, 0, NULL);
}

void CGroupWinsockDlg::ShowMsg(CString strMsg)
{
	m_Show.SetSel(-1, -1);// �ѹ�궨λ���ı����λ��
	m_Show.ReplaceSel(strMsg + _T("\n\r\n"));// ������滻Ϊ�ı���Ϣ
}

DWORD WINAPI CGroupWinsockDlg::ClientThreadProc(LPVOID lpParameter)
{
	CString GroupIP;
	CString strMsg;
	ASSERT(lpParameter);
	CGroupWinsockDlg* m_pMainWnd = (CGroupWinsockDlg*)lpParameter;

	if((m_pMainWnd->s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		AfxMessageBox(_T("socket failed!"));
		goto _Error_End;
	}

	m_pMainWnd->local.sin_family = AF_INET;
	m_pMainWnd->local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	m_pMainWnd->local.sin_port = htons(m_pMainWnd->GetDlgItemInt(IDC_EDIT_PORT));
	
	// ��ȡ�ı������ı�����ת����������-------------@
	
	m_pMainWnd->m_GroupIP.GetWindowTextW(GroupIP);
	char szIpAddr[16] = {0};
	USES_CONVERSION;
	strcpy_s(szIpAddr, 16, T2A(GroupIP));
	
	m_pMainWnd->ipmr.imr_multiaddr.S_un.S_addr = inet_addr(szIpAddr);
	//ipmr.imr_multiaddr.S_un.S_addr = inet_addr("234.5.6.7");
	m_pMainWnd->ipmr.imr_interface.S_un.S_addr = htonl(INADDR_ANY);
	if(bind(m_pMainWnd->s, (SOCKADDR*)&(m_pMainWnd->local), sizeof(m_pMainWnd->local)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("bind failed!"));
		goto _Error_End;
	}

	if(setsockopt(m_pMainWnd->s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&(m_pMainWnd->ipmr), sizeof(m_pMainWnd->ipmr)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("setsockopt failed!"));
		goto _Error_End;
	}
	
	//AfxMessageBox(_T("sucess"));
	m_pMainWnd->ShowMsg(_T("sucess join to 234.5.6.7......."));
	
	
	while(TRUE /*&& !(m_ClientItem.m_pMainWnd->bShutDown)*/)
	{
		//m_pMainWnd->ShowMsg(_T("while\r\n"));
		if(m_pMainWnd->SOCKET_Select(m_pMainWnd->s, 100, TRUE))
		{
			TCHAR szBuf[MAX_BUF_SIZE] = {0};
			int iRet = NULL;
			if(iRet = recvfrom(m_pMainWnd->s, (char*)szBuf, MAX_BUF_SIZE, 0,(struct sockaddr*)&(m_pMainWnd->from), &(m_pMainWnd->len)) == SOCKET_ERROR)// ���ؽ��յ����ֽ���
			{
				AfxMessageBox(_T("recvfrom failed"));
				goto _Error_End;
			}
			if(iRet)
			{
				strMsg.Format(_T("%s"),szBuf);
				strMsg = szBuf;
				//strMsg = _T("�ͻ��ˣ�") + m_ClientItem.m_strIp + _T(">") + strMsg;
				m_pMainWnd->ShowMsg(strMsg);
				//m_ClientItem.m_pMainWnd->SendClientsMsg(strMsg, &m_ClientItem);
			}
			else
			{// �ͻ����뿪�����Լ�д���룬socket�ڲ����
				//strMsg = _T("�ͻ��ˣ�") + m_ClientItem.m_strIp + _T(">�뿪�����ң�");
				//m_ClientItem.m_pMainWnd->ShowMsg(strMsg);
				//m_ClientItem.m_pMainWnd->RemoveClientFromArray(m_ClientItem);
				break;

			}
			
		}
		Sleep(500);
	}
_Error_End:
	if(m_pMainWnd->s != INVALID_SOCKET)
	{
		closesocket(m_pMainWnd->s);
	}
	WSACleanup();
	return TRUE;
}

BOOL CGroupWinsockDlg::SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut>1000?1000:nTimeOut;
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


void CGroupWinsockDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText;
	ASSERT(s != INVALID_SOCKET);
	GetDlgItemText(IDC_EDIT_MSG, strText);
	if(!strText.IsEmpty() && SOCKET_Select(s, 100, FALSE))
	{
		//AfxMessageBox(strText);
		if(sendto(s, (char*)strText.GetBuffer(), strText.GetLength()*sizeof(TCHAR), 0, (struct sockaddr*)&remote, sizeof(remote)) == SOCKET_ERROR)
		{
			AfxMessageBox(_T("sendto failed"));
			return;
		}
		SetDlgItemText(IDC_EDIT_MSG, _T(""));
		ShowMsg(strText);
	}
}
