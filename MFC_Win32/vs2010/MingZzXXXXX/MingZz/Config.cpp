#include "StdAfx.h"
#include "Config.h"


CConfig::CConfig(void)
{
}


CConfig::~CConfig(void)
{
}

void CConfig::WriteDefaultInfo()
{
    WritePrivateProfileString(_T("Config"),_T("Port"),_T("8000"),_T(".\\Config.ini")); //上线端口
    WritePrivateProfileString(_T("Config"),_T("Max"),_T("1000"),_T(".\\Config.ini")); //最大上线主机
    WritePrivateProfileString(_T("Config"),_T("DefaultPath"),_T(""),_T(".\\Config.ini")); //默认下载路径
    WritePrivateProfileString(_T("Config"),_T("Sound"),_T("1"),_T(".\\Config.ini")); //是否启用声音
}

UINT CConfig::GetPort()
{
    return GetPrivateProfileInt(_T("Config"),_T("Port"),8000,_T(".\\Config.ini"));
}

UINT CConfig::GetMax()
{
    return GetPrivateProfileIntW(_T("Config"),_T("Max"),1000,_T(".\\Config.ini"));
}

UINT CConfig::GetSound()
{
    return GetPrivateProfileIntW(_T("Config"),_T("Sound"),1,_T(".\\Config.ini"));
}