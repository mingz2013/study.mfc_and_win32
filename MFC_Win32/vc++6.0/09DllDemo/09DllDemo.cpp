// 09DllDemo.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "09DllDemo.h"
#include <stdio.h>
HMODULE g_hModule;
BOOL APIENTRY DllMain( HANDLE hModule, // 本模块句柄
                       DWORD  ul_reason_for_call, // 调用的原因
                       LPVOID lpReserved // 没有被使用
					 )
{
    switch (ul_reason_for_call)
	{
	        // 动态链接库刚被映射到某个进程的地址空间
		case DLL_PROCESS_ATTACH:
			g_hModule = (HMODULE)hModule; // 保存模块句柄
			break;
		// 应用程序创建了一个新的线程	
		case DLL_THREAD_ATTACH:
		// 应用程序某个线程正常终止
		case DLL_THREAD_DETACH:
		// 动态链接库将被卸载
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

// 自定义 导出函数
void ExportFunc(LPCTSTR pszContent)
{
	char sz[MAX_PATH];
	::GetModuleFileName(g_hModule,sz,MAX_PATH);
	::MessageBox(NULL,pszContent,strrchr(sz,'\\')+1,MB_OK);
}
