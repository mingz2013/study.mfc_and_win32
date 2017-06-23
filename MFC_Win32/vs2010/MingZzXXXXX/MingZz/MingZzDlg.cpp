
// MingZzDlg.cpp : ʵ���ļ�
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





// CMingZzDlg �Ի���




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


// CMingZzDlg ��Ϣ�������

BOOL CMingZzDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->m_max = 1000;
	this->m_port = 8000;
	this->m_Sound = 0;
	UpdateMain(8000);
	::CloseHandle(CreateThread(0,0,OninitSocket,(LPVOID)this,0,0)); //�����߳�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMingZzDlg::OnPaint()
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
HCURSOR CMingZzDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMingZzDlg::UpdateMain(int port)
{
    m_imagelist.Create(32,32,ILC_COLOR24|ILC_MASK,1,1);//λͼ�б���
    CBitmap bmp;// ����һ��λͼ�Ķ���
    for(int i=0;i<8;i++)
    {
        bmp.LoadBitmapW(IDB_BITMAP1+i);//����λͼ
        m_imagelist.Add(&bmp,RGB(255,255,255));//��ӵ��б�
        bmp.DeleteObject();// ɾ�����ͷ���Դ
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
    const UINT t[9] = {1001,1002,1003,1004,1005,1006,0,1007,1008};// 9������ť��ID
	m_toolbar.CreateEx(this);// ����������
    m_toolbar.SetButtons(t,9);// ���ð�ť  ID���飬ID����
    m_toolbar.SetSizes(CSize(60,56),CSize(24,24));// �ߴ�����  ��ť��С��ͼ���С
    m_toolbar.SetButtonText(0,_T("�ļ�����"));// ͼ����ı���Ϣ
    m_toolbar.SetButtonText(1,_T("��Ļ���"));
    m_toolbar.SetButtonText(2,_T("�����ն�"));
    m_toolbar.SetButtonText(3,_T("���̹���"));
    m_toolbar.SetButtonText(4,_T("��Ƶ���"));
    m_toolbar.SetButtonText(5,_T("ж������"));
    m_toolbar.SetButtonText(7,_T("��������"));
    m_toolbar.SetButtonText(8,_T("�������"));
    m_toolbar.GetToolBarCtrl().SetImageList(&m_imagelist);// ����ͼ���б�

    BOOL hbar = m_statusbar.Create(this);// ����״̬��
    UINT b[2]={1009,1010};// 2��
    hbar = m_statusbar.SetIndicators(b,2);// ���飬 ��Ŀ
    m_statusbar.SetPaneInfo(0,b[0],SBPS_NORMAL,400);// һЩ����
    m_statusbar.SetPaneInfo(1,b[1],SBPS_NORMAL,180);
    CString ListenPort; // 
    ListenPort.Format(_T("�����˿ڣ�%d"),port);
    m_statusbar.SetPaneText(0,ListenPort);// �����ı�
    m_statusbar.SetPaneText(1,_T("����������0 ̨"));
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);// ����
	/*
    m_mainicon.Create(16,16,ILC_COLOR24|ILC_MASK,1,0);
    m_mainicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_USER)));
    m_mainicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_CAM)));
    m_list.SetImageList(&m_mainicon,LVSIL_SMALL);
	*/

    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// �б��������
    m_list.InsertColumn(0,_T("����λ��"),LVCFMT_LEFT,160);// ������
    m_list.InsertColumn(1,_T("IP��ַ"),LVCFMT_LEFT,110);
    m_list.InsertColumn(2,_T("����ϵͳ"),LVCFMT_LEFT,90);
    m_list.InsertColumn(3,_T("����״̬"),LVCFMT_LEFT,60);
    m_list.InsertColumn(4,_T("����˰汾��"),LVCFMT_LEFT,100);

    GetClientRect(&m_rect);// ��ȡ�ͻ������δ�С
}


BOOL CMingZzDlg::PreTranslateMessage(MSG* pMsg)// ���������Ϣ��
{// ���غ��������������س�����ESC���˳����������
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


void CMingZzDlg::OnSize(UINT nType, int cx, int cy)
{// �������С�仯ʱ��������Ϣ

	//CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CDialog::OnSize(nType, cx, cy);
    if(nType == SIZE_MINIMIZED)// ��С��
    {
        return;
    }
    // TODO: �ڴ˴������Ϣ����������
    CWnd *pWnd;// ������ָ��
    pWnd = GetDlgItem(IDC_LIST);     //��ȡ�ؼ����
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

bool CMingZzDlg::InitSocket() //��ʼ��SOCKET
{
    WSADATA WSAData;
	WSAStartup(MAKEWORD(2,2), &WSAData);
	SOCKADDR_IN saddr;

    s=::socket(AF_INET,SOCK_STREAM,0);
	if(s==SOCKET_ERROR)
	{
		MessageBox(_T("��������ʧ��"),_T("��ʾ"),MB_OK|MB_ICONWARNING);
        return false;
	}
	
	saddr.sin_family=AF_INET;
	saddr.sin_addr.S_un.S_addr=INADDR_ANY;
	saddr.sin_port=htons(m_port);
	
	int nRet;
    nRet=::bind(s,(SOCKADDR *)&saddr,sizeof(saddr));
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("�󶨶˿�ʧ��"),_T("��ʾ"),MB_OK|MB_ICONWARNING);
        return false;
	}

	nRet=listen(s,m_max);
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("�����˿�ʧ��"),_T("��ʾ"),MB_OK|MB_ICONWARNING);
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

DWORD WINAPI CMingZzDlg::OninitSocket(LPVOID self) //��ʼ��Socket�߳�
{
    CMingZzDlg* t = (CMingZzDlg*)self;
    t->InitSocket();
    return 0;
}

void CMingZzDlg::AddHost(SOCKET sock,SOCKADDR_IN addr) //�����������
{
    GetNewItemData(sock,addr);
    return;
}

void CMingZzDlg::GetNewItemData(SOCKET sock,SOCKADDR_IN addr) //��ȡ�µ���Ŀ����
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int t = MessageBoxW(_T("ȷ��Ҫ�˳�������"),_T("��ʾ"),MB_YESNO|MB_ICONINFORMATION);
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


LRESULT CMingZzDlg::OnAddHost(WPARAM wparam, LPARAM lparam) // ����������Ϣ��
{
	CItemData *t = (CItemData*) wparam;
	int i = m_list.GetItemCount();
	m_list.InsertItem(i, t->m_Address, 0);
	m_list.SetItemText(i, 1, t->m_IP);
	m_list.SetItemText(i, 2, t->m_OS);
	m_list.SetItemText(i, 3, _T("δ����"));
	m_list.SetItemText(i, 4, t->m_Ver);
	m_list.SetItemData(i, (DWORD)t);
	ShowOnLine();
	if(m_Sound == 1)
	{
		PlaySoundW(_T("Sound\\online.wav"), 0, SND_FILENAME|SND_ASYNC);
	}
	return 0;
}

LRESULT CMingZzDlg::OnOffLine(WPARAM wparam, LPARAM lparam) // ����������Ϣ��
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

void CMingZzDlg::ShowOnLine() // ������������   ״̬��
{
	int c = m_list.GetItemCount();
	CString online;
	TCHAR * szText;
	online.Format(_T("����������%d ̨"), c);
	szText = online.GetBuffer(online.GetLength());
	::SendMessageW(m_statusbar, SB_SETTEXTW, (WPARAM)1, (LPARAM)szText);
	online.ReleaseBuffer();
}

void CMingZzDlg::OnFileManager()
{
    CItemData *t;
    t = GetSelItemInfo();// �õ���ǰѡ�е���
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