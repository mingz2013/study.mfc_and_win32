
// ClientDlg.cpp : ʵ���ļ�
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


// CClientDlg �Ի���




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


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_port = PORT;
	InitSystem();
	CreateThread(0,0,OninitSocket,this,0,0); //�����߳�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

void CClientDlg::InitSystem()
{

	BOOL hbar = m_statusbar.Create(this);// ����״̬��
    UINT b[2]={1009,1010};// 2��
    hbar = m_statusbar.SetIndicators(b,2);// ���飬 ��Ŀ
    m_statusbar.SetPaneInfo(0,b[0],SBPS_NORMAL,400);// һЩ����
    m_statusbar.SetPaneInfo(1,b[1],SBPS_NORMAL,180);
    CString ListenPort; // 
    ListenPort.Format(_T("�����˿ڣ�%d"),PORT);
    m_statusbar.SetPaneText(0,ListenPort);// �����ı�
    m_statusbar.SetPaneText(1,_T("����������0 ̨"));
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);// ����

	m_ListClient.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// �б��������
    m_ListClient.InsertColumn(0,_T("����λ��"),LVCFMT_LEFT,160);// ������
    m_ListClient.InsertColumn(1,_T("IP��ַ"),LVCFMT_LEFT,110);
    m_ListClient.InsertColumn(2,_T("����ϵͳ"),LVCFMT_LEFT,90);
    m_ListClient.InsertColumn(3,_T("����״̬"),LVCFMT_LEFT,60);
    m_ListClient.InsertColumn(4,_T("����˰汾��"),LVCFMT_LEFT,100);

    GetClientRect(&m_rect);// ��ȡ�ͻ������δ�С
	return;
}

void CClientDlg::OnSize(UINT nType, int cx, int cy)
{// �ı��Сʱ
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(nType == SIZE_MINIMIZED)// ��С��
    {
        return;
    }
    // TODO: �ڴ˴������Ϣ����������
    CWnd *pWnd;// ������ָ��
    pWnd = GetDlgItem(IDC_LIST_CLIENT);     //��ȡ�ؼ����
    if(pWnd)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
    {
        CRect rect,rect_l;   //��ȡ�ؼ��仯ǰ��С
        GetClientRect(&rect_l);// ��ȡû�仯֮ǰ�Ĵ�С
        pWnd->GetWindowRect(&rect);// �ؼ�����
        ScreenToClient(&rect);
        rect.right = cx;// �ұ� = ���ڵ��ұ�
        rect.bottom= rect.bottom + (rect_l.bottom - m_rect.bottom);// �߶ȵı仯
        pWnd->MoveWindow(rect);//���ÿؼ���С
		
        RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);// ����һ��״̬��
    }
    /*
    else
    {
        delete pWnd;
    }
    */
    GetClientRect(&m_rect);// �ٴλ�ȡһ�´��ڵľ���
}


BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{// ���غ����������س����رճ���
	// TODO: �ڴ����ר�ô����/����û���

	if(pMsg->message == WM_KEYDOWN)// ������Ϣ
	{
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey == VK_RETURN || nVirtKey == VK_ESCAPE)// �س���  || ESC��
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
	if(bRead)// �ɶ�
	{
		iRet = select(0, &fdset, NULL, NULL, &tv);
	}
	else
	{// ��д
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

DWORD WINAPI CClientDlg::OninitSocket(LPVOID self) //��ʼ��Socket�߳�
{
    CClientDlg* t = (CClientDlg*)self;
    t->InitSocket();
    return 0;
}
bool CClientDlg::InitSocket() //��ʼ��SOCKET
{
    WSADATA WSAData;
	WSAStartup(MAKEWORD(2,2), &WSAData);
	sockaddr_in SLisenaddr;

    SLisen=::socket(AF_INET,SOCK_STREAM,0);
	if(SLisen==SOCKET_ERROR)
	{
		MessageBox(_T("��������ʧ��"),_T("��ʾ"),MB_OK|MB_ICONWARNING);
        return false;
	}
	
	SLisenaddr.sin_family=AF_INET;
	SLisenaddr.sin_addr.S_un.S_addr=INADDR_ANY;
	SLisenaddr.sin_port=htons(m_port);
	
	int nRet;
    nRet=::bind(SLisen,(SOCKADDR *)&SLisenaddr,sizeof(SLisenaddr));
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("�󶨶˿�ʧ��"),_T("��ʾ"),MB_OK|MB_ICONWARNING);
        return false;
	}

	nRet=listen(SLisen,MAXCOUNT);
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("�����˿�ʧ��"),_T("��ʾ"),MB_OK|MB_ICONWARNING);
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

void CClientDlg::GetNewItemData(SOCKET sock,SOCKADDR_IN addr) //��ȡ�µ���Ŀ����
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