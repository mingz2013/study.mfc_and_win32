
// ServMgrView.cpp : CServMgrView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CServMgrView ����/����

CServMgrView::CServMgrView()
{
	// TODO: �ڴ˴���ӹ������

}

CServMgrView::~CServMgrView()
{
}

BOOL CServMgrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

void CServMgrView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
	SetWindowLong(GetListCtrl().m_hWnd, GWL_STYLE, GetWindowLong(GetListCtrl().m_hWnd, GWL_STYLE)|LVS_REPORT);// LVS_REPORT ������ʽ
	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	GetListCtrl().InsertColumn(0, _T("��������"), LVCFMT_LEFT, 150);
	GetListCtrl().InsertColumn(1, _T("����״̬"), LVCFMT_LEFT, 90);
	GetListCtrl().InsertColumn(2, _T("��������"), LVCFMT_LEFT, 90);
	GetListCtrl().InsertColumn(3, _T("�ļ�·��"), LVCFMT_LEFT, 230);
	GetListCtrl().InsertColumn(4, _T("��������"), LVCFMT_LEFT, 600);
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


// CServMgrView ���

#ifdef _DEBUG
void CServMgrView::AssertValid() const
{
	CListView::AssertValid();
}

void CServMgrView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CServMgrDoc* CServMgrView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServMgrDoc)));
	return (CServMgrDoc*)m_pDocument;
}
#endif //_DEBUG


// CServMgrView ��Ϣ�������
