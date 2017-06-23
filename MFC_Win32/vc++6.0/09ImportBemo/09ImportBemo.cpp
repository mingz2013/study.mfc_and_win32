// 09ImportBemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

//#include "09DllDemo.h"
//#pragma comment(lib,"09DllDemo")

// 声明函数原型
typedef void(*PFNEXPORTFUNC)(LPCTSTR);

int main(int argc, char* argv[])
{
	// 加载Dll库
	HMODULE hModule = ::LoadLibrary("..\\09DllDemo\\Debug\\09DllDemo.dll");
	if(hModule != NULL)
	{// 取得ExportFunc函数的地址
		PFNEXPORTFUNC mExportFunc = (PFNEXPORTFUNC)::GetProcAddress(hModule,"ExportFunc");
		if(mExportFunc != NULL)
		{
			mExportFunc("大家好！");
		}
		// 卸载Dll库
		::FreeLibrary(hModule);
	}
	// 像调用其它函数一样调用09DllDemo.dll库导出的函数
	//ExportFunc("大家好！");
	return 0;
}
