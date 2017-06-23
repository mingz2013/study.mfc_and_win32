
#include<tchar.h>
#include<Windows.h>
#include"resource.h"


HINSTANCE appInstance;


BOOL  EnableShutDownPriv()
{// 提权函数
	HANDLE hToken = NULL;
	TOKEN_PRIVILEGES tkp = {0};
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken))// 打开权限令牌
	{
		return FALSE;
	}
	if(!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	return TRUE;

}

BOOL ReSetWindows(DWORD dwFlags, BOOL bForce)
{        //功能函数 重启 关机 注销
	// Check the param;
	if(dwFlags != EWX_LOGOFF && dwFlags != EWX_REBOOT && dwFlags != EWX_SHUTDOWN)
	{
		return FALSE;
	}

	// Get the OS Version
	OSVERSIONINFO osvi = {0};
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if(!GetVersionEx(&osvi))// 获得版本
	{
		return FALSE;
	}

	if(osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)// NT系统
	{
		EnableShutDownPriv();// 提升当前进程的权限

	}

	dwFlags |=(bForce != FALSE)?EWX_FORCE:EWX_FORCEIFHUNG;// bForce为TRUE，强制杀掉进程，为FORCE，先通知一下再杀掉
	return ExitWindowsEx(dwFlags,0);// 关机 重启 或 注销
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{// 窗口消息出理函数
	switch(uMsg)
	{
	case WM_INITDIALOG:// 捕获窗口初始化的消息
		{
	
			HWND hComBox = GetDlgItem(hwndDlg,IDC_COMBO);// 获取下拉框的句柄
			SendMessage(hComBox, CB_INSERTSTRING, 0,(LPARAM) _T("注销")); // 向下拉框发送插入数据的消息
			SendMessage(hComBox, CB_INSERTSTRING, 1,(LPARAM) _T("重启"));
			SendMessage(hComBox, CB_INSERTSTRING, 2,(LPARAM) _T("关机"));
		}
		break;
	case WM_COMMAND:// 命令消息
		{
		switch(wParam)
		{
			case IDC_BUTTON1:
				{
					TCHAR szText[20];
					GetDlgItemText(hwndDlg, IDC_COMBO,szText,20); // 获取组合框文本
					if(_tcscmp(szText,_T("注销")) == 0)
					{
						ReSetWindows(EWX_LOGOFF,FALSE);
					}
					else if(_tcscmp(szText,_T("重启")) == 0)
					{
						ReSetWindows(EWX_REBOOT,FALSE);
					}
					else if(_tcscmp(szText,_T("关机")) == 0)
					{
						ReSetWindows(EWX_SHUTDOWN,FALSE);
					}
					//MessageBox(hwndDlg, _T("执行按钮"),_T("提示"),MB_OK);

				}
				break;
			case IDC_BUTTON2:
				{
				int iRet = MessageBox(hwndDlg, _T("关闭按钮"),_T("提示"),MB_OKCANCEL);
				if(iRet == IDOK)// 确认按钮
				{
				EndDialog(hwndDlg,IDC_BUTTON2);// 关闭对话框
				}
				break;
				}
			case IDCANCEL:// 叉号
				MessageBox(hwndDlg, _T("关闭按钮"),_T("提示"),MB_OK);
				EndDialog(hwndDlg,IDC_BUTTON2);// 关闭对话框
				break;
		default:
			break;
		}
		break;
		}
	default:
		break;

	}
	return 0;
}


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	appInstance = hInstance;
	if(_tcscmp(lpCmdLine, _T("/r")) == 0)
	{
		ReSetWindows(EWX_REBOOT,FALSE);
	}
	else if(_tcscmp(lpCmdLine, _T("/s")) == 0)
	{
		ReSetWindows(EWX_SHUTDOWN,FALSE);
	}
	else if(_tcscmp(lpCmdLine, _T("/l")) == 0)
	{
		ReSetWindows(EWX_LOGOFF,FALSE);
	}
	else
	{
		//AfxMessageBox(_T("命令错误，，，/r 重启，/s 关机， /l 注销\n"));
	
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc);//弹出一个窗口
	}

	
	return 0;
}