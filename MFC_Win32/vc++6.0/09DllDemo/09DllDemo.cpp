// 09DllDemo.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "09DllDemo.h"
#include <stdio.h>
HMODULE g_hModule;
BOOL APIENTRY DllMain( HANDLE hModule, // ��ģ����
                       DWORD  ul_reason_for_call, // ���õ�ԭ��
                       LPVOID lpReserved // û�б�ʹ��
					 )
{
    switch (ul_reason_for_call)
	{
	        // ��̬���ӿ�ձ�ӳ�䵽ĳ�����̵ĵ�ַ�ռ�
		case DLL_PROCESS_ATTACH:
			g_hModule = (HMODULE)hModule; // ����ģ����
			break;
		// Ӧ�ó��򴴽���һ���µ��߳�	
		case DLL_THREAD_ATTACH:
		// Ӧ�ó���ĳ���߳�������ֹ
		case DLL_THREAD_DETACH:
		// ��̬���ӿ⽫��ж��
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

// �Զ��� ��������
void ExportFunc(LPCTSTR pszContent)
{
	char sz[MAX_PATH];
	::GetModuleFileName(g_hModule,sz,MAX_PATH);
	::MessageBox(NULL,pszContent,strrchr(sz,'\\')+1,MB_OK);
}
