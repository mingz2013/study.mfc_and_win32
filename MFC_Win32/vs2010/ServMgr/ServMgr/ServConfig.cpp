#include "StdAfx.h"
#include "ServConfig.h"


CServConfig::CServConfig(void)
{
}


CServConfig::~CServConfig(void)
{
}


CServItem *CServConfig::EnumServList()
{
	
	SC_HANDLE hSCM = OpenSCManager( 
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);// 这里出错了
	if(NULL == hSCM)
	{
		return NULL;// 从这里返回了
	}
	CServItem *pServPre,*pServNext,*pServHeader;
	LPENUM_SERVICE_STATUS pServStatus = NULL;
	DWORD dwBytesNeeded = 0, dwServCound = 0, dwResume = 0, dwRealBytes = 0;
	BOOL bRet = EnumServicesStatus(hSCM, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &dwBytesNeeded, &dwServCound, &dwResume); 
	if(!bRet&&GetLastError() == ERROR_MORE_DATA)
	{
		dwRealBytes = dwBytesNeeded;
		pServStatus = new ENUM_SERVICE_STATUS[dwRealBytes + 1];
		ZeroMemory(pServStatus, dwRealBytes + 1);
		bRet = EnumServicesStatus(hSCM, SERVICE_WIN32, SERVICE_STATE_ALL, pServStatus, dwRealBytes, &dwBytesNeeded, &dwServCound, &dwResume);
		if(!bRet)
		{
			CloseServiceHandle(hSCM);
			return NULL;
		}
	}
	else
	{
		CloseServiceHandle(hSCM);
		return NULL;
	}

	pServPre = pServNext;
	for(DWORD dwIdx = 0; dwIdx < dwServCound; dwIdx++)
	{
		pServNext = new CServItem;
		pServNext->m_strServName = pServStatus[dwIdx].lpServiceName;
		pServNext->m_strServDispName = pServStatus[dwIdx].lpDisplayName;
		pServNext->m_dwServStatus = pServStatus[dwIdx].ServiceStatus.dwCurrentState;
		(pServHeader == NULL)?(pServHeader = pServNext):pServHeader;
		(pServPre == NULL)?(pServPre = pServNext):(pServPre->m_pNext = pServNext,pServPre = pServNext);
	}
	delete[]pServStatus;
	return pServHeader;
}
