
// CListCtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCListCtrlApp:
// �йش����ʵ�֣������ CListCtrl.cpp
//

class CCListCtrlApp : public CWinApp
{
public:
	CCListCtrlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCListCtrlApp theApp;