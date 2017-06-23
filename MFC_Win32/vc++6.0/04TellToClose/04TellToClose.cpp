// 04TellToClose.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<windows.h>


int main(int argc, char* argv[])
{
	// 查找标题为“无标题 - 记事本”的窗口
	// 也可以使用类名来查找，如“::FindWindow("Notepad",NULL);”
	HWND hWnd = ::FindWindow(NULL,"无标题 - 记事本");
	if(hWnd != NULL)
	{
		// 向目标窗口发送 WM_CLOSE 消息,将窗口关闭
		::SendMessage(hWnd,WM_CLOSE,0,0);

	}
	return 0;
}
