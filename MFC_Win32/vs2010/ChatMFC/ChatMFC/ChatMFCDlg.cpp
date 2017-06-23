
// ChatMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatMFC.h"
#include "ChatMFCDlg.h"
#include "afxdialogex.h"
//#include "InitChat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatMFCDlg 对话框




CChatMFCDlg::CChatMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ID, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CChatMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(HDN_ITEMCLICK, 0, &CChatMFCDlg::OnHdnItemclickListId)
//ON_NOTIFY(NM_RCLICK, IDC_LIST_ID, &CChatMFCDlg::OnNMRClickListId)
//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ID, &CChatMFCDlg::OnLvnItemchangedListId)
//ON_NOTIFY(HDN_ITEMCLICK, 0, &CChatMFCDlg::OnHdnItemclickListId)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ID, &CChatMFCDlg::OnLvnItemchangedListId)
END_MESSAGE_MAP()


// CChatMFCDlg 消息处理程序

BOOL CChatMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	InitChat();
	
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatMFCDlg::OnPaint()
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
HCURSOR CChatMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CChatMFCDlg::OnHdnItemclickListId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	// 
//	*pResult = 0;
//}


//void CChatMFCDlg::OnNMRClickListId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	//AfxMessageBox((char)pNMHDR);
//	AfxMessageBox(_T("弹出右键菜单"));
//	// 弹出右键菜单
//	//pResult->
//	*pResult = 0;
//}


//void CChatMFCDlg::OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}


//void CChatMFCDlg::OnHdnItemclickListId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	AfxMessageBox(_T("qqqqqqqq"));
//	*pResult = 0;
//}


void CChatMFCDlg::OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
