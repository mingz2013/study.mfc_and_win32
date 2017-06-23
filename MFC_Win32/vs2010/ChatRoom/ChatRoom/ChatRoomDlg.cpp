
// ChatRoomDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "ChatRoomDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Inc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatRoomDlg �Ի���




CChatRoomDlg::CChatRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatRoomDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bShowAll = FALSE;
	m_ListenSock = INVALID_SOCKET;
}

void CChatRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHATSHOW, m_EditChatShow);
}

BEGIN_MESSAGE_MAP(CChatRoomDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_RADIO_SERVER, &CChatRoomDlg::OnBnClickedRadioServer)
	ON_BN_CLICKED(IDC_BUTTON_NET, &CChatRoomDlg::OnBnClickedButtonNet)
	ON_BN_CLICKED(IDC_BUTTON_STARTSEV, &CChatRoomDlg::OnBnClickedButtonStartsev)
	ON_BN_CLICKED(IDC_RADIO_CLIENT, &CChatRoomDlg::OnBnClickedRadioClient)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatRoomDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CChatRoomDlg::OnBnClickedButtonConnect)
	ON_EN_CHANGE(IDC_EDIT_CHATMSG, &CChatRoomDlg::OnEnChangeEditChatmsg)
	ON_BN_CLICKED(IDC_BUTTON_STOPCON, &CChatRoomDlg::OnBnClickedButtonStopcon)
	ON_BN_CLICKED(IDC_BUTTON_STOPSEV, &CChatRoomDlg::OnBnClickedButtonStopsev)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CChatRoomDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_MORE, &CChatRoomDlg::OnBnClickedButtonMore)
	ON_COMMAND(ID_MENU_TRAYICON, &CChatRoomDlg::OnMenuTrayicon)

	ON_MESSAGE(WM_TRAYICON_MSG, OnTrayCallBackMsg)// ����������Ϣ��������
	ON_COMMAND(ID_MENU_SHOW, &CChatRoomDlg::OnMenuShow)
	ON_COMMAND(ID_MENU_EXIT, &CChatRoomDlg::OnMenuExit)
END_MESSAGE_MAP()


// CChatRoomDlg ��Ϣ�������

BOOL CChatRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	DlgAllInit();
	ExtendDlg(FALSE);
	bShowAll = FALSE;
	m_bIsServer = -1;
	m_ListenSock = INVALID_SOCKET;
	m_ConnectSock = INVALID_SOCKET;
	m_hListenThread = NULL;
	m_hConnectThread = NULL;
	bShutDown = FALSE;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatRoomDlg::OnPaint()
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
HCURSOR CChatRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatRoomDlg::DlgAllInit()
{// ��ʼ��


	// ���ÿؼ�
	EnableWindow(IDC_BUTTON_SEND, FALSE);

	EnableWindow(IDC_BUTTON_STOPCON,FALSE);
	EnableWindow(IDC_STATIC,FALSE);
	EnableWindow(IDC_EDIT_LOCALPORT,FALSE);
	EnableWindow(IDC_BUTTON_STARTSEV,FALSE);
	EnableWindow(IDC_BUTTON_STOPSEV,FALSE);
	EnableWindow(IDC_BUTTON_SEND,FALSE);


	CheckRadioButton(IDC_RADIO_CLIENT,IDC_RADIO_CLIENT,IDC_RADIO_CLIENT);// ��ѡ���ʼֵ
	SetDlgItemText(IDC_IPADDRESS, _T("127.0.0.1"));
	SetDlgItemText(IDC_EDIT_SERVERPORT, _T("10000"));
	SetDlgItemText(IDC_EDIT_LOCALPORT, _T("10000"));

}


BOOL CChatRoomDlg::EnableWindow(UINT uID, BOOL bEnable )
{
	// �Կؼ���ֹ������
	//return GetDlgItem(uID)->EnableWindow(bEnable);
	return ::EnableWindow(GetDlgItem(uID)->GetSafeHwnd(),bEnable);
}

void CChatRoomDlg::OnBnClickedRadioServer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iRet = -1;
	if(FALSE == m_bIsServer)
	{
		int iRet = MessageBox(_T("���������ҵĿͻ��ˣ��Ƿ��˳���"),_T("��ʾ"),MB_OKCANCEL);
		if(IDOK == iRet)
		{
			StopClient();
		}
		else
		{
			CheckRadioButton(IDC_RADIO_CLIENT, IDC_RADIO_SERVER, IDC_RADIO_CLIENT);
		}
	}
	if(IDOK == iRet || -1 == m_bIsServer)
	{
		// ���ÿؼ�������˱�ѡ��
		EnableWindow(IDC_STATIC,FALSE);
		EnableWindow(IDC_IPADDRESS,FALSE);
		EnableWindow(IDC_STATIC,FALSE);
		EnableWindow(IDC_EDIT_SERVERPORT,FALSE);
		EnableWindow(IDC_BUTTON_CONNECT,FALSE);
		EnableWindow(IDC_BUTTON_STOPCON,FALSE);

		// �����ؼ�

		EnableWindow(IDC_STATIC,TRUE);
		EnableWindow(IDC_EDIT_LOCALPORT,TRUE);
		EnableWindow(IDC_BUTTON_STARTSEV,TRUE);
		//EnableWindow(IDC_BUTTON_STOPSEV,TRUE);
	}

}


void CChatRoomDlg::ExtendDlg(BOOL bShow)
{
	static CRect m_DlgRectLarge(0,0,0,0);
	static CRect m_DlgRectSmall(0,0,0,0);

	static CRect m_GroupRectLarge(0,0,0,0);
	static CRect m_GroupRectSmall(0,0,0,0);

	if(m_DlgRectLarge.IsRectNull())//��һ�ε���/
	{
		GetWindowRect(&m_DlgRectLarge);
	    m_DlgRectSmall = m_DlgRectLarge;
	    m_DlgRectSmall.right -= 285;

		::GetWindowRect(GetDlgItem(IDCANCEL)->GetSafeHwnd(), m_GroupRectLarge);
		m_GroupRectSmall = m_GroupRectLarge;
	    m_GroupRectSmall.right -= 275;
	}

	

	if(bShow)
	{
		bShowAll = TRUE;
		SetWindowPos(NULL, m_DlgRectLarge.left, m_DlgRectLarge.top, m_DlgRectLarge.Width(), m_DlgRectLarge.Height(), SWP_NOZORDER|SWP_NOMOVE);
		::SetWindowPos(GetDlgItem(IDCANCEL)->GetSafeHwnd(),NULL,  m_GroupRectLarge.left, m_GroupRectLarge.top, m_GroupRectLarge.Width(), m_GroupRectLarge.Height(),SWP_NOZORDER|SWP_NOMOVE); 
	}
	else
	{
		bShowAll = FALSE;
		SetWindowPos(NULL, m_DlgRectSmall.left, m_DlgRectSmall.top, m_DlgRectSmall.Width(), m_DlgRectSmall.Height(), SWP_NOZORDER|SWP_NOMOVE);
		::SetWindowPos(GetDlgItem(IDCANCEL)->GetSafeHwnd(),NULL,  m_GroupRectSmall.left, m_GroupRectSmall.top, m_GroupRectSmall.Width(), m_GroupRectSmall.Height(),SWP_NOZORDER|SWP_NOMOVE);
	}
}

void CChatRoomDlg::OnBnClickedButtonNet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(bShowAll)
	{
			ExtendDlg(FALSE);
	}
	else
	{
		ExtendDlg(TRUE);
	}
}


void CChatRoomDlg::OnBnClickedButtonStartsev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_hListenThread = CreateThread(NULL, 0, ListenThreadFunc, this, 0, NULL);

	/*
	
	*/
}

void CChatRoomDlg::OnBnClickedRadioClient()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iRet = -1;
	if(TRUE == m_bIsServer)
	{
		int iRet = MessageBox(_T("���������ҵķ���ˣ��Ƿ��˳���"),_T("��ʾ"),MB_OKCANCEL);
		if(IDOK == iRet)
		{
			StopServer();
		}
		else
		{
			CheckRadioButton(IDC_RADIO_CLIENT, IDC_RADIO_SERVER, IDC_RADIO_SERVER);
		}
	}
	if(IDOK == iRet || -1 == m_bIsServer)
	{
		// �����ؼ����ͻ��˱�ѡ��
		EnableWindow(IDC_STATIC,TRUE);
		EnableWindow(IDC_IPADDRESS,TRUE);
		EnableWindow(IDC_STATIC,TRUE);
		EnableWindow(IDC_EDIT_SERVERPORT,TRUE);
		EnableWindow(IDC_BUTTON_CONNECT,TRUE);
		//EnableWindow(IDC_BUTTON_STOPCON,TRUE);

		// ���ÿؼ�

		EnableWindow(IDC_STATIC,FALSE);
		EnableWindow(IDC_EDIT_LOCALPORT,FALSE);
		EnableWindow(IDC_BUTTON_STARTSEV,FALSE);
		EnableWindow(IDC_BUTTON_STOPSEV,FALSE);
	}
}




void CChatRoomDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strMsg;
	GetDlgItemText(IDC_EDIT_CHATMSG, strMsg);
	if(TRUE == m_bIsServer)
	{
		strMsg = _T("����������") + strMsg;
		ShowMsg(strMsg);
		SendClientsMsg(strMsg);
	}
	else if(FALSE == m_bIsServer)
	{
		CString strTmp = _T("���ؿͻ��ˣ���") + strMsg;
		ShowMsg(strTmp);
		OutputDebugString((LPWSTR)strMsg.GetBuffer());
		int iSend = send(m_ConnectSock, (char*)strMsg.GetBuffer(), strMsg.GetLength()*sizeof(TCHAR), 0);
		
	}
	else
	{
		ShowMsg(_T("ϵͳ��Ϣ�� ���Ƚ����������ã�"));
	}
	strMsg.ReleaseBuffer();
	SetDlgItemText(IDC_EDIT_CHATMSG, _T(""));
}


void CChatRoomDlg::OnBnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_hConnectThread = CreateThread(NULL, 0, ConnectThreadFunc, this, 0, NULL);
}


void CChatRoomDlg::OnEnChangeEditChatmsg()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strMsg;
	GetDlgItemText(IDC_EDIT_CHATMSG, strMsg);
	if(strMsg.IsEmpty())
	{
		EnableWindow(IDC_BUTTON_SEND, FALSE);
	}
	else
	{
		EnableWindow(IDC_BUTTON_SEND);
	}
}


void CChatRoomDlg::OnBnClickedButtonStopcon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	StopClient();
}


void CChatRoomDlg::OnBnClickedButtonStopsev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	StopServer();
}


void CChatRoomDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(TRUE == m_bIsServer)
	{
		StopServer();
	}
	else if(FALSE == m_bIsServer)
	{
		StopClient();
	}
	OnCancel();
}


void CChatRoomDlg::OnBnClickedButtonMore()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����˵�
	CPoint pt;// һ�� �� �� ����
	CRect mRect;// ������
	CMenu mMenu, *pMenu = NULL;// �˵�����
	GetDlgItem(IDC_BUTTON_MORE)->GetWindowRect(&mRect);// ȡ�� ���๦�� ��ť�ľ���
	pt = mRect.BottomRight();// ȡ�����½ǵĵ�
	pt.y = mRect.top + 10;
	mMenu.LoadMenu(IDR_MENU1);// ����һ���˵���Դ
	pMenu = mMenu.GetSubMenu(0);// ��Ϊ����˵�����ʾ��ָ���Ӳ˵���
	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);// �����˵�

}
BOOL CChatRoomDlg::TrayMyIcon(BOOL bAdd)
{ // ���������̺���************************
	BOOL bRet = FALSE;
	NOTIFYICONDATA tnd;// �ṹ��
	tnd.cbSize = sizeof(NOTIFYICONDATA);// ��С
	//tnd.hWnd = m_hWnd; // �����򴰿ڵľ��������GetSafeHwnd();���ر�������
	tnd.hWnd = GetSafeHwnd();
	tnd.uID = IDR_MAINFRAME;// ͼ���ID
	if(TRUE == bAdd)// ��ӻ���ɾ������ͼ��
	{
		tnd.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;// �������õĹ���
		tnd.uCallbackMessage = WM_TRAYICON_MSG;// �ص�����Ϣ,�������ڵ�
		tnd.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));// ��һ��ͼ��
		_tcscpy_s(tnd.szTip, sizeof(tnd.szTip), _T("ChatRoom"));// ������ȥʱ��ʾ���ı���ʾ
		ShowWindow(SW_MINIMIZE);// ��С�����ڣ����ɲ���
		ShowWindow(SW_HIDE);// ���ش���
		bRet = Shell_NotifyIcon(NIM_ADD, &tnd);// ����Ҫ�ĺ������������ͼ��
	}
	else
	{
		ShowWindow(SW_SHOWNA);// ��ʾ������
		SetForegroundWindow();// ���ó�ǰ������
		bRet = Shell_NotifyIcon(NIM_DELETE, &tnd);// ɾ������ͼ��
	}
	return bRet;
}



void CChatRoomDlg::OnMenuTrayicon()
{
	// TODO: �ڴ���������������
	TrayMyIcon();
}

LRESULT CChatRoomDlg::OnTrayCallBackMsg(WPARAM wparam, LPARAM lparam)
{//�Զ�����Ϣ WM_TRAYICON_MSG ����Ϣ��Ӧ����
	switch(lparam)// lparam ������Ϣ��
	{
	case WM_RBUTTONUP:// ����Ҽ�����
		{
			CPoint pt;// һ�� �� �� ����
			CMenu mMenu, *pMenu = NULL;
			mMenu.LoadMenu(IDR_MENU2);// ����һ���˵���Դ
			pMenu = mMenu.GetSubMenu(0);// ��Ϊ����˵�����ʾ��ָ���Ӳ˵���
			GetCursorPos(&pt);
			SetForegroundWindow();// ǰ������
			pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);// �����˵�
			break;
		}
	case WM_LBUTTONDBLCLK:// ���˫��
		{
			ShowWindow(SW_RESTORE);
			SetForegroundWindow();
			TrayMyIcon(FALSE);// ɾ��ͼ��
			break;
		}
	default:break;
	}
	return FALSE;
}


void CChatRoomDlg::OnMenuShow()
{
	// TODO: �ڴ���������������
	ShowWindow(SW_RESTORE);
	TrayMyIcon(FALSE);// ɾ��ͼ��
}


void CChatRoomDlg::OnMenuExit()
{
	// TODO: �ڴ���������������
	TrayMyIcon(FALSE);// ɾ��ͼ��
	OnBnClickedButtonClose();// �˳�����
}
