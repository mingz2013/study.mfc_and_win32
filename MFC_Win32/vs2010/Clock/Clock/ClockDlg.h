
// ClockDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
//#include "resource.h"


// CClockDlg �Ի���
class CClockDlg : public CDialogEx
{
// ����
public:
	CClockDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditCtrl;
	static void CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);
};


