
// DianMingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DianMing.h"
#include "DianMingDlg.h"
#include "afxdialogex.h"

#include <afxdb.h>#include <odbcinst.h>

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


// CDianMingDlg 对话框



CDianMingDlg::CDianMingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDianMingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDianMingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDianMingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDianMingDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDianMingDlg 消息处理程序

BOOL CDianMingDlg::OnInitDialog()
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

void CDianMingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDianMingDlg::OnPaint()
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
HCURSOR CDianMingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDianMingDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDatabase database; 
	CString sSql; 
	CString sItem1, sItem2,sItem3; 
	CString sDriver; 
	CString sDsn; 
	CString sFile,sPath; 
	//获取主程序所在路径,存在sPath中 
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH); 
	sPath.ReleaseBuffer (); 
	int nPos; 
	nPos=sPath.ReverseFind ('\\'); 
	sPath=sPath.Left (nPos); 
	sFile = sPath + _T("\\List.xls");     // 将被读取的Excel文件名 
	// 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"  
	sDriver = GetExcelDriver(); 
	if (sDriver.IsEmpty()) 
	{ 
		// 没有发现Excel驱动 
		AfxMessageBox(_T("没有安装Excel驱动!")); 
		return; 
	} 
	// 创建进行存取的字符串 
	sDsn.Format(_T("ODBC;DRIVER={%s};DSN=' ';DBQ=%s"), sDriver, sFile);     TRY 
	{ 
		// 打开数据库(既Excel文件) 
		database.Open(NULL, false, false, sDsn); 
		CRecordset recset(&database); 

		// 设置读取的查询语句. 
		sSql = _T("SELECT Num,Name, Age FROM Exceldemo ORDER BY Name "); //设置索引顺序 
		// 执行查询语句 
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly); 
				// 获取查询结果 
		while (!recset.IsEOF()) 
		{ 
			//读取Excel内部数值 
			recset.GetFieldValue(_T("Num"), sItem1); 
			recset.GetFieldValue(_T("Name"), sItem2); 
			recset.GetFieldValue(_T("Age"), sItem3); 
			
			//显示记取的内容 
			m_ExcelList.AddString( sItem1 + _T(" --> ")+sItem2+ _T(" --> ")+sItem3 ); 
			// 移到下一行 
			recset.MoveNext(); 
		} 
		// 关闭数据库 
		database.Close(); 
	} 
	CATCH(CDBException, e) 
	{ 
		// 数据库操作产生异常时... 
		AfxMessageBox(_T("数据库错误: " )+ e->m_strError); 
	} 
	END_CATCH; 
}
CString CDianMingDlg::GetExcelDriver()
{
    char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = (char*)szBuf;
    CString sDriver;
 
    // 获取已安装驱动的名称(涵数在odbcinst.h里)
    if (!SQLGetInstalledDrivers((LPWSTR)szBuf, cbBufMax, &cbBufOut))
        return _T("");
    
    // 检索已安装的驱动是否有Excel...
    do
    {
        if (strstr(pszBuf, _T("Excel")) != 0)
        {
            //发现 !
            sDriver = CString(pszBuf);
            break;
        }
        pszBuf = strchr(pszBuf, '\0') + 1;
    }
    while (pszBuf[1] != '\0');
 
    return sDriver;
}