// 09ImportBemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

//#include "09DllDemo.h"
//#pragma comment(lib,"09DllDemo")

// ��������ԭ��
typedef void(*PFNEXPORTFUNC)(LPCTSTR);

int main(int argc, char* argv[])
{
	// ����Dll��
	HMODULE hModule = ::LoadLibrary("..\\09DllDemo\\Debug\\09DllDemo.dll");
	if(hModule != NULL)
	{// ȡ��ExportFunc�����ĵ�ַ
		PFNEXPORTFUNC mExportFunc = (PFNEXPORTFUNC)::GetProcAddress(hModule,"ExportFunc");
		if(mExportFunc != NULL)
		{
			mExportFunc("��Һã�");
		}
		// ж��Dll��
		::FreeLibrary(hModule);
	}
	// �������������һ������09DllDemo.dll�⵼���ĺ���
	//ExportFunc("��Һã�");
	return 0;
}
