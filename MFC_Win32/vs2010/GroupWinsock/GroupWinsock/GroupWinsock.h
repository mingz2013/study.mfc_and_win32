
// GroupWinsock.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGroupWinsockApp:
// �йش����ʵ�֣������ GroupWinsock.cpp
//

class CGroupWinsockApp : public CWinApp
{
public:
	CGroupWinsockApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGroupWinsockApp theApp;