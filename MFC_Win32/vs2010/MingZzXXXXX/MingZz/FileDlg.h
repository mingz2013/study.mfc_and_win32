#pragma once
#include "afxcmn.h"
#include "resource.h"
#include "FileView.h"
#include "FileTrans.h"


// CFileDlg �Ի���

class CFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileDlg)

public:
	CFileDlg(CWnd* pParent = NULL, SOCKET sock = NULL);   // ��׼���캯��
	virtual ~CFileDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
private:
	SOCKET m_sock;
public:
	CTabCtrl m_Tab;
	afx_msg void OnClose();
	void UpDateMainFrame();
	CStatusBar m_statusbar;
	CRect m_rect;
	CFileView* m_fileview;
	CFileTrans *m_filetrans;
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
