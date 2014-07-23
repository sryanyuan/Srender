#ifndef _INC_RENDERWND_
#define _INC_RENDERWND_
//////////////////////////////////////////////////////////////////////////
#include "SrenderDef.h"
#include <windows.h>
#include "SRObject.h"
//////////////////////////////////////////////////////////////////////////
class SRENDER_API SRRenderWnd : public SRObject
{
	SRRUNTIME_DECLARE()

public:
	SRRenderWnd();

	virtual ~SRRenderWnd();

public:
	bool Create(const char* _pszWndTitle, int _nWndWidth, int _nWndHeight);
	void ShowWindow(bool bShow = true);

public:
	//	event processor
	virtual bool OnCreate(LPCREATESTRUCT _pCreateStruct, LRESULT& _lRet);
	virtual bool OnLButtonDown(UINT _uFlag, const POINT& _ptPos, LRESULT& _lRet);
	virtual bool OnClose(LRESULT& _lRet);
	virtual bool OnDestroy(LRESULT& _lRet);

	//	frame function
	virtual void DrawFrame()	{}

public:
	inline bool IsWindow()
	{
		if(0 == m_hWnd)
		{
			return false;
		}

		return ::IsWindow(m_hWnd) == TRUE ? true : false;
	}

protected:
	static LRESULT CALLBACK _WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

protected:
	RECT m_rcWnd;

	MUTABLE_PROPERTY_BASETYPE(HWND, m_hWnd, HWND);
};
//////////////////////////////////////////////////////////////////////////
#endif