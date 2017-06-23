
// ComboBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComboBox.h"
#include "ComboBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CComboBoxDlg �Ի���




CComboBoxDlg::CComboBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComboBoxDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComboBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_ComboBox);
}

BEGIN_MESSAGE_MAP(CComboBoxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, &CComboBoxDlg::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CComboBoxDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CComboBoxDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CComboBoxDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CComboBoxDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CComboBoxDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CComboBoxDlg ��Ϣ�������

BOOL CComboBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_ComboBox.AddString(_T("��1��"));// �����Ŀ
	m_ComboBox.AddString(_T("��2��"));
	m_ComboBox.AddString(_T("��3��"));
	m_ComboBox.AddString(_T("��4��"));
	m_ComboBox.AddString(_T("��5��"));
	m_ComboBox.AddString(_T("��6��"));
	m_ComboBox.AddString(_T("��7��"));
	m_ComboBox.AddString(_T("��8��"));
	m_ComboBox.AddString(_T("��9��"));
	m_ComboBox.AddString(_T("��10��"));
	m_ComboBox.InsertString(0,_T("0"));// ������Ŀ
	m_ComboBox.InsertString(1,_T("1"));
	m_ComboBox.InsertString(2,_T("2"));
	m_ComboBox.InsertString(3,_T("3"));
	m_ComboBox.SetCurSel(0);// ��ʼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CComboBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CComboBoxDlg::OnPaint()
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
HCURSOR CComboBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CComboBoxDlg::OnBnClickedButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ComboBox.DeleteString(0);// ɾ����0��
}


void CComboBoxDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ComboBox.ResetContent();// ɾ��������
}


void CComboBoxDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num = m_ComboBox.GetCount();
	num =num;

	
	
}


void CComboBoxDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ComboBox.InsertString(m_ComboBox.GetCount(),_T("���"));
}


void CComboBoxDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num = m_ComboBox.GetCurSel();// ��ȡ��ǰ������һ��
}


void CComboBoxDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_ComboBox.GetLBText(m_ComboBox.GetCurSel(), str);
	AfxMessageBox(str);
}
