
// ExcelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Excel.h"
#include "ExcelDlg.h"
#include "afxdialogex.h"

#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"


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


// CExcelDlg 对话框




CExcelDlg::CExcelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExcelDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CExcelDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CExcelDlg 消息处理程序

BOOL CExcelDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CExcelDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExcelDlg::OnPaint()
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
HCURSOR CExcelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExcelDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CApplication app;
	CWorkbooks books;
	CWorkbook book;
	CWorksheets sheets;
	CWorksheet sheet;
	CRange range;
	CRange iCell;
	LPDISPATCH lpDisp;
	COleVariant vResult;
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if(!app.CreateDispatch(L"Excel.Application"))
	{
	AfxMessageBox(L"无法启动Excel服务器!");
	return;
	}
	books.AttachDispatch(app.get_Workbooks());
	lpDisp = books.Open(_T("d:\\test.xls"),covOptional, covOptional, covOptional, covOptional, covOptional,covOptional, covOptional, covOptional, covOptional, covOptional,covOptional, covOptional, covOptional,covOptional);
	
	//得到Workbook
	book.AttachDispatch(lpDisp);
	//得到Worksheets
	sheets.AttachDispatch(book.get_Worksheets());
 
	//得到当前活跃sheet
	//如果有单元格正处于编辑状态中，此操作不能返回，会一直等待
	lpDisp=book.get_ActiveSheet();
	sheet.AttachDispatch(lpDisp);
	//读取第一个单元格的值
	range.AttachDispatch(sheet.get_Cells());
	range.AttachDispatch(range.get_Item (COleVariant((long)2),COleVariant((long)1)).pdispVal );
	/*COleVariant*/ vResult =range.get_Value2();
	CString str;
	if(vResult.vt == VT_BSTR) //字符串
	{
	str=vResult.bstrVal;
	}
	else if (vResult.vt==VT_R8) //8字节的数字
	{
	str.Format(L"%f",vResult.dblVal);
	}
 
	/*else if(vResult.vt==VT_DATE) //时间格式
	{
	SYSTEMTIME st;
	VariantTimeToSystemTime(&vResult.date, &st);
	}
	else if(vResult.vt==VT_EMPTY) //单元格空的
	{
	str="";
	}*/  
    books.Close(); 
    app.Quit();  			// 退出
	//释放对象  
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	OnOK();
	MessageBox(str);
}
