
// CreateThreadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CreateThread.h"
#include "CreateThreadDlg.h"
#include "afxdialogex.h"

#include "TestDlg.h"
#include "UIThreadApp.h"

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


// CCreateThreadDlg �Ի���




CCreateThreadDlg::CCreateThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCreateThreadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCreateThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCreateThreadDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCreateThreadDlg ��Ϣ�������

BOOL CCreateThreadDlg::OnInitDialog()
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

void CCreateThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCreateThreadDlg::OnPaint()
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
HCURSOR CCreateThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)// ��һ��

{
	int tipMsg = (int)lpParameter;
	CString strMsg;
	while(true)
	{
		OutputDebugString(strMsg);
		strMsg.Format(_T("%d\n"),tipMsg++);
		Sleep(1000);
	//AfxMessageBox(strMsg);
	}
	return 0;
}
UINT __cdecl MyControllingFunction( LPVOID lpParameter )// �̺߳������������,
{
	CCreateThreadDlg *pThisDlg = (CCreateThreadDlg*)lpParameter;// ��ȡ��ָ��
	int tipMsg = pThisDlg->m_Num;// ��ȡ���Ա����
	CString strMsg;
	while(true)
	{
		OutputDebugString(strMsg);
		strMsg.Format(_T("%d\n"),tipMsg++);
		Sleep(1000);
	//AfxMessageBox(strMsg);
	}
	return 0;
}

UINT __cdecl MyThreadPorc( LPVOID lpParameter )
{
	CCreateThreadDlg *pThisDlg = (CCreateThreadDlg*)lpParameter;// ��ȡ��ָ��

	//CTestDlg dlg;
	//dlg.DoModal();// �����Ի���
	CTestDlg * pTestDlg = new CTestDlg;
	pTestDlg->Create(IDD_DIALOG1,NULL);
	pTestDlg->ShowWindow(SW_SHOW);

	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//Sleep(5000);
	return 0;
}

void CCreateThreadDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Num = 100;
	/*/ ��һ��
	DWORD dwThreadID = 0;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)123, 0, &dwThreadID); 
	CloseHandle(hThread);
	*/
	// �ڶ���
	//CWinThread* pThread = AfxBeginThread(MyThreadPorc, this);// this, ������ָ�룬�������������ɾ�̬��Ա��������������Ҫ����thisָ��
	// �Զ��ͷţ�����д����


	AfxBeginThread(RUNTIME_CLASS(CUIThreadApp));

}
