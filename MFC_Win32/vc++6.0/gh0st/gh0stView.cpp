// gh0stView.cpp : implementation of the CGh0stView class
//

#include "stdafx.h"
#include "gh0st.h"

#include "gh0stDoc.h"
#include "gh0stView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGh0stView

IMPLEMENT_DYNCREATE(CGh0stView, CView)

BEGIN_MESSAGE_MAP(CGh0stView, CView)
	//{{AFX_MSG_MAP(CGh0stView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGh0stView construction/destruction

CGh0stView::CGh0stView()
{
	// TODO: add construction code here

}

CGh0stView::~CGh0stView()
{
}

BOOL CGh0stView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGh0stView drawing

void CGh0stView::OnDraw(CDC* pDC)
{
	CGh0stDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGh0stView printing

BOOL CGh0stView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGh0stView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGh0stView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGh0stView diagnostics

#ifdef _DEBUG
void CGh0stView::AssertValid() const
{
	CView::AssertValid();
}

void CGh0stView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGh0stDoc* CGh0stView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGh0stDoc)));
	return (CGh0stDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGh0stView message handlers
