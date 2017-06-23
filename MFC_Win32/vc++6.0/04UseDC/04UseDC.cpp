// 04UseDC.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include<windows.h>

int APIENTRY WinMain(HINSTANCE hInstance,                 //04UseDC工程下，当然，也可以是一个控制台程序
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	HDC hdc;
	HWND hWnd;
	char sz[] = "大家好";

	// 查找记事本程序的窗口句柄
	hWnd = ::FindWindow("notepad",NULL);
	// 如果记事本程序正在运行，就向其客户区绘制文本
	while(::IsWindow(hWnd)) // IsWindow 函数用于判断一个窗口句柄是否有效
	{
		hdc = ::GetDC(hWnd);
		::TextOut(hdc,10,10,sz,strlen(sz));
		::ReleaseDC(hWnd,NULL);
		::Sleep(1000);
	}

	::MessageBox(NULL,"记事本程序已经退出","04UseDC",MB_OK);

	return 0;
}



