
// ComboBox.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CComboBoxApp:
// �йش����ʵ�֣������ ComboBox.cpp
//

class CComboBoxApp : public CWinApp
{
public:
	CComboBoxApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CComboBoxApp theApp;