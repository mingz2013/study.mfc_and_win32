//"ChatMFCDlg.h" :头文件
//

#pragma once
#include "afxcmn.h"
#include "resource.h"


// CChatMFCDlg 对话框
class CChatMFCDlg : public CDialogEx
{
// 构造
public:
	CChatMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
