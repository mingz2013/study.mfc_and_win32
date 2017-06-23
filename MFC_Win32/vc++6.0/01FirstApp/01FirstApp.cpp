// 01FirstApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include<windows.h> // 包含MessageBox函数声明的头文件

//#pragma comment(lib,"mylib.lib")   其中mylib.lib 是目标库文件

int main(int argc, char* argv[])
{
	// printf("Hello World!\n");   // 原helloword中的

	// 调用API函数MessageBox

	int nSelect = ::MessageBox(NULL,"Hello,Windows XP","Greetings",MB_OKCANCEL);  // “::”表示这是一个全局函数，以与c++类的成员函数相区分

	if(nSelect == IDOK)
	{
		printf("用户选择了“确定”按钮\n");
	}
	else
	{
		printf("用户选择了“取消”按钮\n");
	}

	return 0;
}

