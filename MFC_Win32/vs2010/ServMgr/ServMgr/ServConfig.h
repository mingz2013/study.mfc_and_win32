#pragma once
#include <WinSvc.h>
#pragma comment(lib,"Advapi32.lib")

class CServItem
{
	// ����ڵ���Ϣ
public:
	CString m_strServName;// ������ʵ����
	CString m_strServDispName;// ������ʾ����
	DWORD m_dwServStatus;// ��ǰ״̬
	CServItem *m_pNext;
	CServItem()
	{
		m_dwServStatus = 0;
		m_pNext = NULL;

	}
};

class CServConfig
{
public:
	CServConfig(void);
	~CServConfig(void);
public:
	CServItem *EnumServList();
};

