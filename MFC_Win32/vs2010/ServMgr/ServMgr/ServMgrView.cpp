
// ServMgrView.cpp : CServMgrView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ServMgr.h"
#endif

#include "ServMgrDoc.h"
#include "ServMgrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServMgrView

IMPLEMENT_DYNCREATE(CServMgrView, CListView)

BEGIN_MESSAGE_MAP(CServMgrView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CServMgrView 构造/析构

CServMgrView::CServMgrView()
{
	// TODO: 在此处添加构造代码

}

CServMgrView::~CServMgrView()
{
}

BOOL CServMgrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CServMgrView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
	SetWindowLong(GetListCtrl().m_hWnd, GWL_STYLE, GetWindowLong(GetListCtrl().m_hWnd, GWL_STYLE)|LVS_REPORT);// LVS_REPORT 报表样式
	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	GetListCtrl().InsertColumn(0, _T("服务名称"), LVCFMT_LEFT, 150);
	GetListCtrl().InsertColumn(1, _T("服务状态"), LVCFMT_LEFT, 90);
	GetListCtrl().InsertColumn(2, _T("启动类型"), LVCFMT_LEFT, 90);
	GetListCtrl().InsertColumn(3, _T("文件路径"), LVCFMT_LEFT, 230);
	GetListCtrl().InsertColumn(4, _T("服务描述"), LVCFMT_LEFT, 600);
	CServConfig m_ServCfg;
	CServItem *m_pHeader = m_ServCfg.EnumServList();
	for(int idx = 0; m_pHeader != NULL; idx++)
	{
		GetListCtrl().InsertItem(idx, _T(""));
		GetListCtrl().SetItemText(idx, 0, m_pHeader->m_strServDispName);
		GetListCtrl().SetItemText(idx, 1,(LPCTSTR)m_pHeader->m_dwServStatus);
		//GetListCtrl().SetItemText(idx, 2, m_pHeader->);
		//GetListCtrl().SetItemText(idx, 3, m_pHeader->m_strServDispName);
		//GetListCtrl().SetItemText(idx, 4, m_pHeader->m_strServDispName);
		m_pHeader = m_pHeader->m_pNext;
	}


}

void CServMgrView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CServMgrView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CServMgrView 诊断

#ifdef _DEBUG
void CServMgrView::AssertValid() const
{
	CListView::AssertValid();
}

void CServMgrView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CServMgrDoc* CServMgrView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServMgrDoc)));
	return (CServMgrDoc*)m_pDocument;
}
#endif //_DEBUG


// CServMgrView 消息处理程序
