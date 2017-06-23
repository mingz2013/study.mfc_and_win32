#pragma once
#include <WinSvc.h>
#pragma comment(lib,"Advapi32.lib")

class CServItem
{
	// 服务节点信息
public:
	CString m_strServName;// 服务真实名称
	CString m_strServDispName;// 服务显示名称
	DWORD m_dwServStatus;// 当前状态
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

