#include "StdAfx.h"
#include "ItemData.h"


CItemData::CItemData(UINT id,SOCKET sock,SOCKADDR_IN *addr,HWND m_hWnd)
{
	this->m_id = id;
    this->m_sock = sock;
    this->m_hWnd = m_hWnd;
   // char *csIP = inet_ntoa(addr->sin_addr);
   // m_IP.Format(_T("%s"),m_str.CharToCString(csIP));
   // m_Address = QQ.IP2Add(m_IP);
    if(m_Address.IsEmpty())
    {
        m_Address.Format(_T("Î´Öª"));
    }
}


CItemData::~CItemData(void)
{
}




void CItemData::Run()
{
    CreateThread(0,0,OnListen,this,0,0);
}
DWORD WINAPI CItemData::OnListen(LPVOID lp)
{
    CItemData* t = (CItemData*)lp;
    t->OnBeginListen();
    return 0;
}

void CItemData::OnBeginListen() //µÈ´ıÍêÉÆ
{
}