
// MyDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

//#define port 12345
// CMyDlg �Ի���
class CMyDlg : public CDialogEx
{
// ����
public:
	CMyDlg(CWnd* pParent = NULL);	// ��׼����
	

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CImageList m_ImageList;
	CImageList m_ImageList_Tree;
	HTREEITEM m_hRoot;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_TreeCtrl;
	afx_msg void OnBnClickedButtonConn();
	WSADATA wsadata;
	SOCKET server;
	sockaddr_in serveraddr;
//	CEdit m_Edit;
	//CString m_addr;
//	CString m_addr;
//	CEdit m_Edit;
	CListCtrl	m_list;
	CTreeCtrl	m_tree;
	CString	m_addr;
	static void SetPubDir(CString path);
	int GetDriverProc(BYTE* DATE);
};
