// CheckDir.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MingZz.h"
#include "CheckDir.h"
#include "afxdialogex.h"


// CCheckDir �Ի���

IMPLEMENT_DYNAMIC(CCheckDir, CDialogEx)

CCheckDir::CCheckDir(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckDir::IDD, pParent)
{

}

CCheckDir::~CCheckDir()
{
}

void CCheckDir::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCheckDir, CDialogEx)
END_MESSAGE_MAP()


// CCheckDir ��Ϣ�������
