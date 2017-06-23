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
	ofn.nFilterIndex = 1;// Ĭ�ϵ�һ��������
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn))// ��ͨ�öԻ���
	{
		//MessageBox(NULL, (LPCWSTR)szFile, TEXT("�ļ���"), MB_OK);
		PlaySound((LPCWSTR)szFile, NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	// SND_SYNC:ͬ��ģʽ��SND_ASYNC:�첽ģʽ
	//SND_LOOP:ѭ����ֱ���������
	MessageBox(NULL,TEXT("���ڲ�������"),TEXT("��ʾ"),MB_OK);
	PlaySound(NULL, NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	MessageBox(NULL,TEXT("����ֹͣ��"),TEXT("��ʾ"),MB_OK);
	}

	
	/*
	//PlaySound(TEXT("D:\\studymyself\\c++\\PlaySound\\PlaySound\\123.wav"), NULL, SND_FILENAME|SND_SYNC);
	PlaySound(TEXT("123.wav"), NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	// SND_SYNC:ͬ��ģʽ��SND_ASYNC:�첽ģʽ
	//SND_LOOP:ѭ����ֱ���������
	MessageBox(NULL,TEXT("���ڲ�������"),TEXT("��ʾ"),MB_OK);
	PlaySound(NULL, NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	MessageBox(NULL,TEXT("����ֹͣ��"),TEXT("��ʾ"),MB_OK);
	*/
	return 0;
}