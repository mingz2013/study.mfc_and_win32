
// CListCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CListCtrl.h"
#include "CListCtrlDlg.h"
#include "afxdialogex.h"

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


// CCListCtrlDlg �Ի���




CCListCtrlDlg::CCListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCListCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CCListCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCListCtrlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCListCtrlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCListCtrlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCListCtrlDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCListCtrlDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCListCtrlDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCListCtrlDlg::OnBnClickedButton7)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, &CCListCtrlDlg::OnLvnEndlabeleditList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CCListCtrlDlg::OnNMRClickList1)
	ON_BN_CLICKED(IDC_BUTTON8, &CCListCtrlDlg::OnBnClickedButton8)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CCListCtrlDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CCListCtrlDlg ��Ϣ�������

BOOL CCListCtrlDlg::OnInitDialog()
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
	LVGROUP PLVGROUP ;

	PLVGROUP.cbSize = sizeof(PLVGROUP);

	//PLVGROUP->cbSize =;// sizeof(LVGROUP*);
	PLVGROUP.mask = LVGF_HEADER;
	PLVGROUP.pszHeader = _T("group1");
	PLVGROUP.cchHeader = sizeof(PLVGROUP.pszHeader);
	PLVGROUP.pszFooter = _T("footer");
	PLVGROUP.cchFooter = sizeof(PLVGROUP.cchFooter);
	PLVGROUP.iGroupId = 1;
	PLVGROUP.stateMask = NULL;
	PLVGROUP.state = NULL;
	PLVGROUP.uAlign= LVGA_FOOTER_CENTER;
	PLVGROUP.pszSubtitle = _T("pszsubtitle");
	PLVGROUP.cchSubtitle = sizeof(PLVGROUP.pszSubtitle);
	PLVGROUP.pszTask = NULL;
	PLVGROUP.cchTask = NULL;
	PLVGROUP.pszDescriptionTop = NULL;
	PLVGROUP.cchDescriptionTop = NULL;
	PLVGROUP.pszDescriptionBottom = NULL;
	PLVGROUP.cchDescriptionBottom = NULL;
	PLVGROUP.iTitleImage = NULL;
	PLVGROUP.iExtendedImage = NULL;
	PLVGROUP.iFirstItem = NULL;
	PLVGROUP.cItems = NULL;
	PLVGROUP.pszSubsetTitle = _T("group1");
	PLVGROUP.cchSubsetTitle = sizeof(PLVGROUP.pszSubsetTitle);
	int id = m_ListCtrl.InsertGroup(m_ListCtrl.GetGroupCount(),&PLVGROUP);
	//m_ListCtrl.InsertItem(



	m_ListCtrl.InsertColumn(0,_T("��0��"),LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(1,_T("��1��"),LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(2,_T("��2��"),LVCFMT_LEFT,100);
	m_ListCtrl.InsertItem(0,_T("000"));
	m_ListCtrl.SetItemText(0,1,_T("abc"));
	m_ListCtrl.InsertItem(1,_T("001"));
	m_ListCtrl.InsertItem(2,_T("002"));
	m_ListCtrl.SetItemText(2,2,_T("22"));
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCListCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCListCtrlDlg::OnPaint()
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
HCURSOR CCListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCListCtrlDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText = m_ListCtrl.GetItemText(2,2);
	AfxMessageBox(strText);
}


void CCListCtrlDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCount = m_ListCtrl.GetSelectedCount();
	CString strText;
	strText.Format(_T("%d"),nCount);
	AfxMessageBox(strText);
}


void CCListCtrlDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCount = m_ListCtrl.GetSelectionMark();
	CString strText;
	strText.Format(_T("%d"),nCount);
	AfxMessageBox(strText);
}


void CCListCtrlDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListCtrl.DeleteAllItems();
}


void CCListCtrlDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListCtrl.DeleteColumn(1);
}


void CCListCtrlDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListCtrl.DeleteItem(1);
}


void CCListCtrlDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListCtrl.SetBkColor(RGB(255,0,0));
}


void CCListCtrlDlg::OnLvnEndlabeleditList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText;
	m_ListCtrl.GetEditControl()->GetWindowTextW(strText);
	m_ListCtrl.SetItemText(pDispInfo->item.iItem,pDispInfo->item.iSubItem,strText);
	*pResult = 0;
}


void CCListCtrlDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCount = m_ListCtrl.GetSelectionMark();
	CString strText;
	strText.Format(_T("%d"),nCount);
	AfxMessageBox(_T("ѡ�е��У�") + strText);
	*pResult = 0;
}


void CCListCtrlDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CCListCtrlDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
