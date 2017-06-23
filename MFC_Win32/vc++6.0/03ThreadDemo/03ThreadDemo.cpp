// 03ThreadDemo.cpp : Defines the entry point for the console application.
// 主程序首先创建了一个辅助线程，打印出辅助线程的ID号，然后等待辅助线程运行结束；
// 辅助线程仅打印出几行字符串，以模拟真正的工作

#include "stdafx.h"
#include<windows.h>

// 线程函数
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	int i = 0;
	while ( i < 20 )
	{
		printf("I am from a thread,count = %d \n",i++);
	}
	return 0;

}

int main(int argc, char* argv[])
{
	HANDLE hThread;
	DWORD dwThreadId;
	// 创建一个线程
	hThread = ::CreateThread(
		NULL, // 默认安全属性
		NULL, // 默认堆栈大小
		ThreadProc, // 线程入口地址 （执行线程的函数）
		NULL, // 传给函数的参数
		0, // 指定线程立即运行
		&dwThreadId); // 返回线程的ID号

	printf("Now another thread has been ctreated. ID = %d \n",dwThreadId);

	// 等待新线程运行结束
	::WaitForSingleObject(hThread,INFINITE);
	::CloseHandle(hThread);
	return 0;
	
}

