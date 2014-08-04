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

	//	user define function
	virtual void OnDrawFrame()	{}
	virtual bool OnEnvCreate()	{return true;}
	virtual void OnEnvDestroy()	{}

public:
	inline bool IsWindow()
	{
		if(0 == m_hWnd)
		{
			return false;
		}

		return ::IsWindow(m_hWnd) == TRUE ? true : false;
	}
	inline IDirect3DDevice9* GetD3DDevice()
	{
		return m_pD3Dev9;
	}

public:
	//	draw
	int DrawQuad();

protected:
	HRESULT InitD3D9();
	void UnInitD3D9();

protected:
	static LRESULT CALLBACK _WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

protected:
	RECT m_rcWnd;
	IDirect3DDevice9* m_pD3Dev9;

	MUTABLE_PROPERTY_BASETYPE(HWND, m_hWnd, HWND);
};
//////////////////////////////////////////////////////////////////////////
#endif