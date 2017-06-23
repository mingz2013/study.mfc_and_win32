#pragma once



// CUIThreadApp

class CUIThreadApp : public CWinThread
{
	DECLARE_DYNCREATE(CUIThreadApp)

protected:
	CUIThreadApp();           // 动态创建所使用的受保护的构造函数
	virtual ~CUIThreadApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


