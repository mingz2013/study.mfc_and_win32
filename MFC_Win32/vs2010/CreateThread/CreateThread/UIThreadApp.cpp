// UIThreadApp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CreateThread.h"
#include "UIThreadApp.h"
#include "TestDlg.h"


// CUIThreadApp

IMPLEMENT_DYNCREATE(CUIThreadApp, CWinThread)

CUIThreadApp::CUIThreadApp()
{
}

CUIThreadApp::~CUIThreadApp()
{
}

BOOL CUIThreadApp::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	CTestDlg dlg;
	dlg.DoModal();
	return FALSE;
}

int CUIThreadApp::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThreadApp, CWinThread)
END_MESSAGE_MAP()


// CUIThreadApp ��Ϣ�������
