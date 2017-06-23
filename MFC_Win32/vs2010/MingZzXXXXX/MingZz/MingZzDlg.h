
// MingZzDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "MySocket.h"
#include "ItemData.h"


// CMingZzDlg 对话框
class CMingZzDlg : public CDialogEx
{
// 构造
public:
	CMingZzDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MINGZZ_DIALOG };

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

private:
	CToolBar m_toolbar;// 工具条类对象
	CImageList m_imagelist;// 图像列表 用于工具条
	CStatusBar m_statusbar;// 状态栏
	CBitmap m_subbmp[6];// 位图
	CImageList m_mainicon; // 其他图标
	void UpdateMain(int port);
	bool InitSocket();

	UINT m_port;
	UINT m_max;
	UINT m_Sound;
	CRect m_rect;// 矩形对象
	SOCKET s;
	static DWORD WINAPI OninitSocket(LPVOID self);
	void AddHost(SOCKET sock,SOCKADDR_IN addr);
	void GetNewItemData(SOCKET sock,SOCKADDR_IN addr);
	
	
public:
	CListCtrl m_list;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CMySocket m_Mysock;
	afx_msg void OnClose();
	LRESULT OnAddHost(WPARAM wparam, LPARAM lparam);
	LRESULT OnOffLine(WPARAM wparam, LPARAM lparam);
	void ShowOnLine();
	void OnFileManager();
	CItemData* GetSelItemInfo();
};
