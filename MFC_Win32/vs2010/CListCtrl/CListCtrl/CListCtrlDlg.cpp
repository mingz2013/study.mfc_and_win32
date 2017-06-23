
// CListCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CListCtrl.h"
#include "CListCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCListCtrlDlg 对话框




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


// CCListCtrlDlg 消息处理程序

BOOL CCListCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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



	m_ListCtrl.InsertColumn(0,_T("第0列"),LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(1,_T("第1列"),LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(2,_T("第2列"),LVCFMT_LEFT,100);
	m_ListCtrl.InsertItem(0,_T("000"));
	m_ListCtrl.SetItemText(0,1,_T("abc"));
	m_ListCtrl.InsertItem(1,_T("001"));
	m_ListCtrl.InsertItem(2,_T("002"));
	m_ListCtrl.SetItemText(2,2,_T("22"));
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCListCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCListCtrlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText = m_ListCtrl.GetItemText(2,2);
	AfxMessageBox(strText);
}


void CCListCtrlDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount = m_ListCtrl.GetSelectedCount();
	CString strText;
	strText.Format(_T("%d"),nCount);
	AfxMessageBox(strText);
}


void CCListCtrlDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount = m_ListCtrl.GetSelectionMark();
	CString strText;
	strText.Format(_T("%d"),nCount);
	AfxMessageBox(strText);
}


void CCListCtrlDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListCtrl.DeleteAllItems();
}


void CCListCtrlDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListCtrl.DeleteColumn(1);
}


void CCListCtrlDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListCtrl.DeleteItem(1);
}


void CCListCtrlDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListCtrl.SetBkColor(RGB(255,0,0));
}


void CCListCtrlDlg::OnLvnEndlabeleditList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
	m_ListCtrl.GetEditControl()->GetWindowTextW(strText);
	m_ListCtrl.SetItemText(pDispInfo->item.iItem,pDispInfo->item.iSubItem,strText);
	*pResult = 0;
}


void CCListCtrlDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nCount = m_ListCtrl.GetSelectionMark();
	CString strText;
	strText.Format(_T("%d"),nCount);
	AfxMessageBox(_T("选中的行：") + strText);
	*pResult = 0;
}


void CCListCtrlDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CCListCtrlDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
