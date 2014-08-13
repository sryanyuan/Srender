#ifndef _INC_MYRENDERWND_
#define _INC_MYRENDERWND_
//////////////////////////////////////////////////////////////////////////
#include <core/SRRenderWnd.h>
#include <core/SIMessageListener.h>
//////////////////////////////////////////////////////////////////////////
class CMyListener : public SIMessageListener
{
public:
	bool OnMessage(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
};

class CMyRenderWnd : public SRRenderWnd
{
public:
	virtual bool OnEnvCreate();
	virtual void OnDrawFrame();
};
//////////////////////////////////////////////////////////////////////////
#endif