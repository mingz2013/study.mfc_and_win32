
// Test_Menu.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTest_MenuApp:
// �йش����ʵ�֣������ Test_Menu.cpp
//

class CTest_MenuApp : public CWinApp
{
public:
	CTest_MenuApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTest_MenuApp theApp;