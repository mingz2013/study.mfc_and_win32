
// ComboBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ComboBox.h"
#include "ComboBoxDlg.h"
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


// CComboBoxDlg 对话框




CComboBoxDlg::CComboBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComboBoxDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComboBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_ComboBox);
}

BEGIN_MESSAGE_MAP(CComboBoxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, &CComboBoxDlg::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CComboBoxDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CComboBoxDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CComboBoxDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CComboBoxDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CComboBoxDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CComboBoxDlg 消息处理程序

BOOL CComboBoxDlg::OnInitDialog()
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
	m_ComboBox.AddString(_T("第1行"));// 添加项目
	m_ComboBox.AddString(_T("第2行"));
	m_ComboBox.AddString(_T("第3行"));
	m_ComboBox.AddString(_T("第4行"));
	m_ComboBox.AddString(_T("第5行"));
	m_ComboBox.AddString(_T("第6行"));
	m_ComboBox.AddString(_T("第7行"));
	m_ComboBox.AddString(_T("第8行"));
	m_ComboBox.AddString(_T("第9行"));
	m_ComboBox.AddString(_T("第10行"));
	m_ComboBox.InsertString(0,_T("0"));// 插入项目
	m_ComboBox.InsertString(1,_T("1"));
	m_ComboBox.InsertString(2,_T("2"));
	m_ComboBox.InsertString(3,_T("3"));
	m_ComboBox.SetCurSel(0);// 初始项

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CComboBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CComboBoxDlg::OnPaint()
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
HCURSOR CComboBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CComboBoxDlg::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ComboBox.DeleteString(0);// 删除第0行
}


void CComboBoxDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ComboBox.ResetContent();// 删除所有项
}


void CComboBoxDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int num = m_ComboBox.GetCount();
	num =num;

	
	
}


void CComboBoxDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ComboBox.InsertString(m_ComboBox.GetCount(),_T("最后"));
}


void CComboBoxDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	int num = m_ComboBox.GetCurSel();// 获取当前项是哪一项
}


void CComboBoxDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_ComboBox.GetLBText(m_ComboBox.GetCurSel(), str);
	AfxMessageBox(str);
}
