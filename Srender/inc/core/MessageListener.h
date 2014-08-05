#ifndef _INC_MESSAGELISTENER
#define _INC_MESSAGELISTENER
//////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <list>
//////////////////////////////////////////////////////////////////////////
class SIMessageListener
{
public:
	virtual bool OnMessage(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam) = 0;
};

typedef std::list<SIMessageListener*> MessageListenerList;
//////////////////////////////////////////////////////////////////////////
#endif