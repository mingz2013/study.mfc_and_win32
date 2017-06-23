
// MingZzDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "MySocket.h"
#include "ItemData.h"


// CMingZzDlg �Ի���
class CMingZzDlg : public CDialogEx
{
// ����
public:
	CMingZzDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MINGZZ_DIALOG };

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

private:
	CToolBar m_toolbar;// �����������
	CImageList m_imagelist;// ͼ���б� ���ڹ�����
	CStatusBar m_statusbar;// ״̬��
	CBitmap m_subbmp[6];// λͼ
	CImageList m_mainicon; // ����ͼ��
	void UpdateMain(int port);
	bool InitSocket();

	UINT m_port;
	UINT m_max;
	UINT m_Sound;
	CRect m_rect;// ���ζ���
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
