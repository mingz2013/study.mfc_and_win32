// 01FirstApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include<windows.h> // ����MessageBox����������ͷ�ļ�

//#pragma comment(lib,"mylib.lib")   ����mylib.lib ��Ŀ����ļ�

int main(int argc, char* argv[])
{
	// printf("Hello World!\n");   // ԭhelloword�е�

	// ����API����MessageBox

	int nSelect = ::MessageBox(NULL,"Hello,Windows XP","Greetings",MB_OKCANCEL);  // ��::����ʾ����һ��ȫ�ֺ���������c++��ĳ�Ա����������

	if(nSelect == IDOK)
	{
		printf("�û�ѡ���ˡ�ȷ������ť\n");
	}
	else
	{
		printf("�û�ѡ���ˡ�ȡ������ť\n");
	}

	return 0;
}

