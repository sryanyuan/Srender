#ifndef _INC_RENDERAPP_
#define _INC_RENDERAPP_
//////////////////////////////////////////////////////////////////////////
#include "SrenderDef.h"
#include "SRObject.h"
#include "MessageListener.h"
#include <Windows.h>
//////////////////////////////////////////////////////////////////////////
class SRRenderWnd;
//////////////////////////////////////////////////////////////////////////
class SRENDER_API SRRenderApp : public SRObject
{
	SINGLETON_DECLARE(SRRenderApp)
	SRRUNTIME_DECLARE()

protected:
	SRRenderApp();

public:
	virtual ~SRRenderApp();

public:
	void AddMsgListener(SIMessageListener* _pListener);
	void RemoveMsgListener(SIMessageListener* _pListener);
	void DestroyMsgListener();

	int MsgLoop();
	void Terminate();

public:
	const MSG* GetLastMsg()				{return &m_stLastMsg;}

protected:
	bool QueryMessageListener(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

public:
	MUTABLE_PROPERTY_BASETYPE(HINSTANCE, m_hInstance, Instance);
	MUTABLE_PROPERTY_BASETYPE(SRRenderWnd*, m_pRenderWnd, RenderWnd);
	MUTABLE_PROPERTY_BASETYPE(HICON, m_hIcon, Icon);
	MUTABLE_PROPERTY_BASETYPE(UINT, m_uFPS, SettingFPS);
	MUTABLE_PROPERTY_BASETYPE(bool, m_bTerminate, Terminate);
	READONLY_PROPERTY_BASETYPE(float, m_fTimeDelta, TimeDelta);

protected:
	MessageListenerList m_xMessageListenerList;
	MSG m_stLastMsg;
};
//////////////////////////////////////////////////////////////////////////
#endif