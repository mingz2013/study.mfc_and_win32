// gh0stView.h : interface of the CGh0stView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GH0STVIEW_H__35D02A41_F077_4B44_831C_50BE58801A41__INCLUDED_)
#define AFX_GH0STVIEW_H__35D02A41_F077_4B44_831C_50BE58801A41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGh0stView : public CView
{
protected: // create from serialization only
	CGh0stView();
	DECLARE_DYNCREATE(CGh0stView)

// Attributes
public:
	CGh0stDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGh0stView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGh0stView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGh0stView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in gh0stView.cpp
inline CGh0stDoc* CGh0stView::GetDocument()
   { return (CGh0stDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GH0STVIEW_H__35D02A41_F077_4B44_831C_50BE58801A41__INCLUDED_)
