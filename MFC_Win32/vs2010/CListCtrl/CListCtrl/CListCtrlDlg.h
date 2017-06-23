
// CListCtrlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CCListCtrlDlg 对话框
class CCListCtrlDlg : public CDialogEx
{
// 构造
public:
	CCListCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLISTCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnLvnEndlabeleditList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton8();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
