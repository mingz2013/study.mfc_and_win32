// 02.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"

#include<windows.h>

int main(int argc, char* argv[])
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	//char* szCommandLine = "notepad"; // 也可以是“notepad.exe”
	char* szCommandLine = "notepad ReadMe.txt"; // 指定了一个 ReadMe.txt 参数，将促使记事本打开此文件
	::CreateProcess(NULL,szCommandLine,NULL,NULL,FALSE,NULL,NULL,NULL,&si,&pi); // 创建一个新的进程
	return 0;
}

