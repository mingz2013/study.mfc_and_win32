#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "MySocket.h"
#include "Conmmon.h"


// CFileView 对话框

class CFileView : public CDialogEx
{
	DECLARE_DYNAMIC(CFileView)

public:
	CFileView(CWnd* pParent = NULL, SOCKET sock = NULL);   // 标准构造函数
	virtual ~CFileView();

// 对话框数据
	enum { IDD = IDD_DIALOG_FILEVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	LPVOID pWnd_s;
	SOCKET m_sock;
	CTreeCtrl m_tree;
	virtual BOOL OnInitDialog();
	CRect m_rect;
	CMySocket m_Mysock;
	void UndateMainFrame();
	CImageList m_imagetree;
	CListCtrl m_list;
	CImageList m_imagelist;
	bool flag;
	int DirCount;
	void SetDisk(DRIVER disk);
	afx_msg void OnNMClickTreeFileview(NMHDR *pNMHDR, LRESULT *pResult);
	void DelChilditem(HTREEITEM hItem);
	CString GetPath(HTREEITEM item);
	HTREEITEM hItem;
	void FileList(FILEINFO fileinfo);
	void SetShowInfo(HTREEITEM Item);
	CString GetRealSize(__int64 size);
	afx_msg void OnNMRClickListFileview(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFileDown();
	HTREEITEM GetSelectTreeItem(CString t);
};
