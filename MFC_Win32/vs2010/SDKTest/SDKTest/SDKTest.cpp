
#include<tchar.h>
#include<Windows.h>
#include"resource.h"


HINSTANCE appInstance;


BOOL  EnableShutDownPriv()
{// ��Ȩ����
	HANDLE hToken = NULL;
	TOKEN_PRIVILEGES tkp = {0};
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken))// ��Ȩ������
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
{        //���ܺ��� ���� �ػ� ע��
	// Check the param;
	if(dwFlags != EWX_LOGOFF && dwFlags != EWX_REBOOT && dwFlags != EWX_SHUTDOWN)
	{
		return FALSE;
	}

	// Get the OS Version
	OSVERSIONINFO osvi = {0};
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if(!GetVersionEx(&osvi))// ��ð汾
	{
		return FALSE;
	}

	if(osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)// NTϵͳ
	{
		EnableShutDownPriv();// ������ǰ���̵�Ȩ��

	}

	dwFlags |=(bForce != FALSE)?EWX_FORCE:EWX_FORCEIFHUNG;// bForceΪTRUE��ǿ��ɱ�����̣�ΪFORCE����֪ͨһ����ɱ��
	return ExitWindowsEx(dwFlags,0);// �ػ� ���� �� ע��
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{// ������Ϣ������
	switch(uMsg)
	{
	case WM_INITDIALOG:// ���񴰿ڳ�ʼ������Ϣ
		{
	
			HWND hComBox = GetDlgItem(hwndDlg,IDC_COMBO);// ��ȡ������ľ��
			SendMessage(hComBox, CB_INSERTSTRING, 0,(LPARAM) _T("ע��")); // ���������Ͳ������ݵ���Ϣ
			SendMessage(hComBox, CB_INSERTSTRING, 1,(LPARAM) _T("����"));
			SendMessage(hComBox, CB_INSERTSTRING, 2,(LPARAM) _T("�ػ�"));
		}
		break;
	case WM_COMMAND:// ������Ϣ
		{
		switch(wParam)
		{
			case IDC_BUTTON1:
				{
					TCHAR szText[20];
					GetDlgItemText(hwndDlg, IDC_COMBO,szText,20); // ��ȡ��Ͽ��ı�
					if(_tcscmp(szText,_T("ע��")) == 0)
					{
						ReSetWindows(EWX_LOGOFF,FALSE);
					}
					else if(_tcscmp(szText,_T("����")) == 0)
					{
						ReSetWindows(EWX_REBOOT,FALSE);
					}
					else if(_tcscmp(szText,_T("�ػ�")) == 0)
					{
						ReSetWindows(EWX_SHUTDOWN,FALSE);
					}
					//MessageBox(hwndDlg, _T("ִ�а�ť"),_T("��ʾ"),MB_OK);

				}
				break;
			case IDC_BUTTON2:
				{
				int iRet = MessageBox(hwndDlg, _T("�رհ�ť"),_T("��ʾ"),MB_OKCANCEL);
				if(iRet == IDOK)// ȷ�ϰ�ť
				{
				EndDialog(hwndDlg,IDC_BUTTON2);// �رնԻ���
				}
				break;
				}
			case IDCANCEL:// ���
				MessageBox(hwndDlg, _T("�رհ�ť"),_T("��ʾ"),MB_OK);
				EndDialog(hwndDlg,IDC_BUTTON2);// �رնԻ���
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
		//AfxMessageBox(_T("������󣬣���/r ������/s �ػ��� /l ע��\n"));
	
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc);//����һ������
	}

	
	return 0;
}