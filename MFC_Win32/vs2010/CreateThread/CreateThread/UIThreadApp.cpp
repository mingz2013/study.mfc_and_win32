// UIThreadApp.cpp : 实现文件
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
	// TODO: 在此执行任意逐线程初始化
	CTestDlg dlg;
	dlg.DoModal();
	return FALSE;
}

int CUIThreadApp::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThreadApp, CWinThread)
END_MESSAGE_MAP()


// CUIThreadApp 消息处理程序
