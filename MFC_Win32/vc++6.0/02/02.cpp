// 02.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"

#include<windows.h>

int main(int argc, char* argv[])
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	//char* szCommandLine = "notepad"; // Ҳ�����ǡ�notepad.exe��
	char* szCommandLine = "notepad ReadMe.txt"; // ָ����һ�� ReadMe.txt ����������ʹ���±��򿪴��ļ�
	::CreateProcess(NULL,szCommandLine,NULL,NULL,FALSE,NULL,NULL,NULL,&si,&pi); // ����һ���µĽ���
	return 0;
}

