
// ChatMFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatMFC.h"
#include "ChatMFCDlg.h"
#include "afxdialogex.h"
//#include "InitChat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatMFCDlg �Ի���




CChatMFCDlg::CChatMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ID, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CChatMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(HDN_ITEMCLICK, 0, &CChatMFCDlg::OnHdnItemclickListId)
//ON_NOTIFY(NM_RCLICK, IDC_LIST_ID, &CChatMFCDlg::OnNMRClickListId)
//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ID, &CChatMFCDlg::OnLvnItemchangedListId)
//ON_NOTIFY(HDN_ITEMCLICK, 0, &CChatMFCDlg::OnHdnItemclickListId)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ID, &CChatMFCDlg::OnLvnItemchangedListId)
END_MESSAGE_MAP()


// CChatMFCDlg ��Ϣ�������

BOOL CChatMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	InitChat();
	
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChatMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CChatMFCDlg::OnHdnItemclickListId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	// 
//	*pResult = 0;
//}


//void CChatMFCDlg::OnNMRClickListId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	//AfxMessageBox((char)pNMHDR);
//	AfxMessageBox(_T("�����Ҽ��˵�"));
//	// �����Ҽ��˵�
//	//pResult->
//	*pResult = 0;
//}


//void CChatMFCDlg::OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


//void CChatMFCDlg::OnHdnItemclickListId(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	AfxMessageBox(_T("qqqqqqqq"));
//	*pResult = 0;
//}


void CChatMFCDlg::OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
