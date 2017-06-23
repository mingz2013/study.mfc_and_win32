#include <Windows.h>
#include <MMSystem.h>

#pragma comment(lib, "winmm.lib")


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{

	OPENFILENAME ofn;
	char szFile[MAX_PATH];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.lpstrFile[0] = TEXT('\0');
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = TEXT("ALL\0*.*\0Text\0*.TXT\0");
	ofn.lpstrFilter = TEXT("*.wav\0*.wav\0");
	ofn.nFilterIndex = 1;// 默认第一个过滤器
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn))// 打开通用对话框
	{
		//MessageBox(NULL, (LPCWSTR)szFile, TEXT("文件名"), MB_OK);
		PlaySound((LPCWSTR)szFile, NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	// SND_SYNC:同步模式，SND_ASYNC:异步模式
	//SND_LOOP:循环，直到程序结束
	MessageBox(NULL,TEXT("正在播放音乐"),TEXT("提示"),MB_OK);
	PlaySound(NULL, NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	MessageBox(NULL,TEXT("音乐停止了"),TEXT("提示"),MB_OK);
	}

	
	/*
	//PlaySound(TEXT("D:\\studymyself\\c++\\PlaySound\\PlaySound\\123.wav"), NULL, SND_FILENAME|SND_SYNC);
	PlaySound(TEXT("123.wav"), NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	// SND_SYNC:同步模式，SND_ASYNC:异步模式
	//SND_LOOP:循环，直到程序结束
	MessageBox(NULL,TEXT("正在播放音乐"),TEXT("提示"),MB_OK);
	PlaySound(NULL, NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	MessageBox(NULL,TEXT("音乐停止了"),TEXT("提示"),MB_OK);
	*/
	return 0;
}