
// Clock.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once


#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CClockApp:
// �йش����ʵ�֣������ Clock.cpp
//

class CClockApp : public CWinApp
{
public:
	CClockApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClockApp theApp;
