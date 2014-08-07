#ifndef _INC_RENDERWND_
#define _INC_RENDERWND_
//////////////////////////////////////////////////////////////////////////
#include "SrenderDef.h"
#include <windows.h>
#include "SRObject.h"
#include "SRVertex.h"
//////////////////////////////////////////////////////////////////////////
class SRENDER_API SRRenderWnd : public SRObject
{
	SRRUNTIME_DECLARE()

public:
	SRRenderWnd();

	virtual ~SRRenderWnd();

public:
	//	window relative
	bool Create(const char* _pszWndTitle, int _nWndWidth, int _nWndHeight);
	void ShowWindow(bool bShow = true);

	//	d3d relative
	template <typename T>
	IDirect3DVertexBuffer9* Gfx_CreateVertexBuffer(DWORD _dwVertexSum, DWORD _dwUsage = D3DUSAGE_WRITEONLY, D3DPOOL _ePool = D3DPOOL_MANAGED)
	{
		if(NULL == m_pD3Dev9)
		{
			return false;
		}

		IDirect3DVertexBuffer9* pVertexBuf = NULL;

		HRESULT hr = m_pD3Dev9->CreateVertexBuffer(sizeof(T) * _dwVertexSum,
			_dwUsage,
			T::FVF,
			_ePool,
			&pVertexBuf,
			NULL);

		if(D3D_OK == hr)
		{
			return pVertexBuf;
		}

		return NULL;
	}

	IDirect3DIndexBuffer9* Gfx_CreateIndexBuffer(DWORD _dwIndexSum, DWORD _dwUsage = D3DUSAGE_WRITEONLY, D3DPOOL _ePool = D3DPOOL_MANAGED, D3DFORMAT _eFormat = D3DFMT_INDEX16);

	bool Gfx_SetViewTransform(const D3DXVECTOR3* _pPosition = NULL, const D3DXVECTOR3* _pTarget = NULL, const D3DXVECTOR3* _pUp = NULL);
	bool Gfx_SetProjectionTransform(float _fFovy = D3DX_PI * 0.5f, float _fZn = 1.0f, float _fZf = 1000.0f);

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
	inline int GetWindowWidth()
	{
		return m_rcWnd.right - m_rcWnd.left;
	}
	inline int GetWindowHeight()
	{
		return m_rcWnd.bottom - m_rcWnd.top;
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