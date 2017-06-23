// FileTrans.cpp : 实现文件
//

#include "stdafx.h"
#include "MingZz.h"
#include "FileTrans.h"
#include "afxdialogex.h"
#include "Conmmon.h"


// CFileTrans 对话框

IMPLEMENT_DYNAMIC(CFileTrans, CDialogEx)

CFileTrans::CFileTrans(CWnd* pParent /*=NULL*/,SOCKET sock)
	: CDialogEx(CFileTrans::IDD, pParent)
{
	m_sock = sock;
}

CFileTrans::~CFileTrans()
{
}

void CFileTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}


BEGIN_MESSAGE_MAP(CFileTrans, CDialogEx)
END_MESSAGE_MAP()


// CFileTrans 消息处理程序
void CFileTrans::OnAddFilelist(int type,wchar_t *path1,wchar_t *path2,wchar_t *size,__int64 *usize)
{
    int i = m_list.GetItemCount();
    if(type == 0)
    {
        m_list.InsertItem(i,_T("下载"),0);
    }
    else
    {
        m_list.InsertItem(i,_T("上传"),1);
    }
    m_list.SetItemText(i,1,path1);
    m_list.SetItemText(i,2,path2);
    m_list.SetItemText(i,3,size);
    m_list.SetItemData(i,(DWORD)usize);
    if(BeginToWork == false)
    {
        BeginToWork = true;
        ::CloseHandle(CreateThread(0,0,BeginToTrans,(LPVOID)this,0,0));
    }
}

DWORD WINAPI CFileTrans::BeginToTrans(LPVOID self)
{
    CFileTrans* t = (CFileTrans*)self;
    t->OnFirstTrans();
    return 0;
}

void CFileTrans::OnFirstTrans()
{
    m_progress.SetPos(0);
    if(m_list.GetItemCount() == 0)
    {
        BeginToWork = false;
        return;
    }
    wchar_t path[260];
    if((m_list.GetItemText(0,0)).Compare(_T("下载")) == 0)
    {
        m_list.GetItemText(0,2,path,_countof(path));
        m_file = new CFile(path,CFile::modeCreate|CFile::modeReadWrite);
        Count = 0;
        MSGINFO msg;
        memset(&msg,0,sizeof(MSGINFO));
        msg.Msg_id = DOWNLOAD;
        memset(path,0,_countof(path));
        m_list.GetItemText(0,1,path,_countof(path));
        memcpy(msg.context,path,sizeof(path));
        m_Mysock.SendCommand(m_sock,(char*)&msg,sizeof(MSGINFO));
    }
    else
    {
        //上传
    }
}


void CFileTrans::UpdateMainFrame()
{
	/*
    m_transicon.Create(16,16,ILC_COLOR24|ILC_MASK,1,0);
    m_transicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_DOWN)));
    m_transicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_UP)));
    m_list.SetImageList(&m_transicon,LVSIL_SMALL);
	*/
    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_list.InsertColumn(0,_T("传输类型"),LVCFMT_LEFT,60);
    m_list.InsertColumn(1,_T("源文件路径"),LVCFMT_LEFT,190);
    m_list.InsertColumn(2,_T("目标文件路径"),LVCFMT_LEFT,190);
    m_list.InsertColumn(3,_T("文件大小"),LVCFMT_LEFT,80);

    m_progress.SetRange(0,100);
}

void CFileTrans::GetFileData(DOWNFILEDATA fi)
{
    if(fi.flag == true)
    {
        Count++;
        float pos;
        m_file->Write(fi.context,fi.size);
        pos = float(m_file->GetLength() * 1.0 / *(__int64*)m_list.GetItemData(0));
        m_progress.SetPos(int(pos*100));
    }
    else
    {
        m_file->Close();
        ::CloseHandle(m_file->m_hFile);
        delete m_file;
        m_list.DeleteItem(0);
        ::CloseHandle(CreateThread(0,0,BeginToTrans,(LPVOID)this,0,0));
    }
}

BOOL CFileTrans::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateMainFrame();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
