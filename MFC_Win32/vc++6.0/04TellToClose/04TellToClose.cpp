// 04TellToClose.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<windows.h>


int main(int argc, char* argv[])
{
	// ���ұ���Ϊ���ޱ��� - ���±����Ĵ���
	// Ҳ����ʹ�����������ң��硰::FindWindow("Notepad",NULL);��
	HWND hWnd = ::FindWindow(NULL,"�ޱ��� - ���±�");
	if(hWnd != NULL)
	{
		// ��Ŀ�괰�ڷ��� WM_CLOSE ��Ϣ,�����ڹر�
		::SendMessage(hWnd,WM_CLOSE,0,0);

	}
	return 0;
}
