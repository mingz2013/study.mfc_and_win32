//"ChatMFCDlg.h" :ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "resource.h"


// CChatMFCDlg �Ի���
class CChatMFCDlg : public CDialogEx
{
// ����
public:
	CChatMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	
	void InitChat();
	void SendMsg(char* SendMsg);

	static DWORD WINAPI DoMsg(LPVOID lparam);
	static DWORD WINAPI RecvMsg(LPVOID lparam);
	
//	afx_msg void OnNMRClickListId(NMHDR *pNMHDR, LRESULT *pResult);
	
	
    
//	afx_msg void OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnHdnItemclickListId(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult);
};
