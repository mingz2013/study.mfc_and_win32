
// DianMingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DianMing.h"
#include "DianMingDlg.h"
#include "afxdialogex.h"

#include <afxdb.h>#include <odbcinst.h>

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


// CDianMingDlg �Ի���



CDianMingDlg::CDianMingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDianMingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDianMingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDianMingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDianMingDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDianMingDlg ��Ϣ�������

BOOL CDianMingDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDianMingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDianMingDlg::OnPaint()
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
HCURSOR CDianMingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDianMingDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDatabase database; 
	CString sSql; 
	CString sItem1, sItem2,sItem3; 
	CString sDriver; 
	CString sDsn; 
	CString sFile,sPath; 
	//��ȡ����������·��,����sPath�� 
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH); 
	sPath.ReleaseBuffer (); 
	int nPos; 
	nPos=sPath.ReverseFind ('\\'); 
	sPath=sPath.Left (nPos); 
	sFile = sPath + _T("\\List.xls");     // ������ȡ��Excel�ļ��� 
	// �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)"  
	sDriver = GetExcelDriver(); 
	if (sDriver.IsEmpty()) 
	{ 
		// û�з���Excel���� 
		AfxMessageBox(_T("û�а�װExcel����!")); 
		return; 
	} 
	// �������д�ȡ���ַ��� 
	sDsn.Format(_T("ODBC;DRIVER={%s};DSN=' ';DBQ=%s"), sDriver, sFile);     TRY 
	{ 
		// �����ݿ�(��Excel�ļ�) 
		database.Open(NULL, false, false, sDsn); 
		CRecordset recset(&database); 

		// ���ö�ȡ�Ĳ�ѯ���. 
		sSql = _T("SELECT Num,Name, Age FROM Exceldemo ORDER BY Name "); //��������˳�� 
		// ִ�в�ѯ��� 
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly); 
				// ��ȡ��ѯ��� 
		while (!recset.IsEOF()) 
		{ 
			//��ȡExcel�ڲ���ֵ 
			recset.GetFieldValue(_T("Num"), sItem1); 
			recset.GetFieldValue(_T("Name"), sItem2); 
			recset.GetFieldValue(_T("Age"), sItem3); 
			
			//��ʾ��ȡ������ 
			m_ExcelList.AddString( sItem1 + _T(" --> ")+sItem2+ _T(" --> ")+sItem3 ); 
			// �Ƶ���һ�� 
			recset.MoveNext(); 
		} 
		// �ر����ݿ� 
		database.Close(); 
	} 
	CATCH(CDBException, e) 
	{ 
		// ���ݿ���������쳣ʱ... 
		AfxMessageBox(_T("���ݿ����: " )+ e->m_strError); 
	} 
	END_CATCH; 
}
CString CDianMingDlg::GetExcelDriver()
{
    char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = (char*)szBuf;
    CString sDriver;
 
    // ��ȡ�Ѱ�װ����������(������odbcinst.h��)
    if (!SQLGetInstalledDrivers((LPWSTR)szBuf, cbBufMax, &cbBufOut))
        return _T("");
    
    // �����Ѱ�װ�������Ƿ���Excel...
    do
    {
        if (strstr(pszBuf, _T("Excel")) != 0)
        {
            //���� !
            sDriver = CString(pszBuf);
            break;
        }
        pszBuf = strchr(pszBuf, '\0') + 1;
    }
    while (pszBuf[1] != '\0');
 
    return sDriver;
}