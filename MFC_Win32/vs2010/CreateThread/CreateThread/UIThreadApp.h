#pragma once



// CUIThreadApp

class CUIThreadApp : public CWinThread
{
	DECLARE_DYNCREATE(CUIThreadApp)

protected:
	CUIThreadApp();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CUIThreadApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


