#include <core/SRRenderWnd.h>
#include <core/SRRenderApp.h>
#include <util/debug.h>
#include <util/SRLogger.h>
//////////////////////////////////////////////////////////////////////////
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif
//////////////////////////////////////////////////////////////////////////
SRRUNTIME_IMPLEMENT(SRRenderWnd, SRObject, SRCLSNAME_SRRENDERWND)

SRRenderWnd::SRRenderWnd()
{
	ZeroMemory(&m_rcWnd, sizeof(m_rcWnd));
	m_hWnd = 0;
	m_pD3Dev9 = NULL;
}

SRRenderWnd::~SRRenderWnd()
{

}


bool SRRenderWnd::Create(const char* _pszWndTitle, int _nWndWidth, int _nWndHeight)
{
	if(0 != m_hWnd)
	{
		return false;
	}

	HINSTANCE hInstance = SRRenderApp::GetInstancePtr()->GetInstance();
	if(NULL == hInstance)
	{
		hInstance = GetModuleHandle(NULL);
		SRRenderApp::GetInstancePtr()->SetInstance(hInstance);
	}

	HICON hIcon = SRRenderApp::GetInstancePtr()->GetIcon();

	m_rcWnd.right = _nWndWidth;
	m_rcWnd.bottom = _nWndHeight;

	WNDCLASS wndClass;
	wndClass.style = CS_DBLCLKS;
	wndClass.lpfnWndProc = &_WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = hIcon;
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = WNDCLS_SRENDER;

	if( !RegisterClass( &wndClass ) )
	{
		DWORD dwError = GetLastError();
		if( dwError != ERROR_CLASS_ALREADY_EXISTS )
		{
			MSGBOX_ERR( "RegisterClass failed");
			LOG(ERROR) << "RegisterClass failed";
			return false;
		}
	}

	LOG(INFO) << "Main render window created.";

	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	m_rcWnd.left = (nScreenWidth - _nWndWidth) / 2;
	m_rcWnd.top = (nScreenHeight - _nWndHeight) / 2;
	m_rcWnd.right = m_rcWnd.left + _nWndWidth;
	m_rcWnd.bottom = m_rcWnd.top + _nWndHeight;

	m_hWnd = CreateWindow( WNDCLS_SRENDER, _pszWndTitle, WS_OVERLAPPEDWINDOW,
		m_rcWnd.left, m_rcWnd.top, _nWndWidth, _nWndHeight, 0,
		0, hInstance, 0 );

	if(0 == m_hWnd)
	{
		DWORD dwError = GetLastError();
		
		MSGBOX_ERR("CreateWindow failed");
		ShowErrorCodeMsgBox(dwError);

		return false;
	}

	if(S_OK != InitD3D9())
	{
		return false;
	}

	SRRenderApp::GetInstancePtr()->SetRenderWnd(this);

	return true;
}

HRESULT SRRenderWnd::InitD3D9()
{
	HRESULT hr = S_OK;

	IDirect3D9* pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if(NULL == pD3D9)
	{
		MSGBOX_ERR("Direct3DCreate9 failed");
		LOG(ERROR) << "Direct3DCreate9 failed";
		return S_FALSE;
	}

	D3DCAPS9 caps;
	pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int nVertexProcessing = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS ddpm;
	ddpm.BackBufferWidth = m_rcWnd.right - m_rcWnd.left;
	ddpm.BackBufferHeight = m_rcWnd.bottom - m_rcWnd.top;
	ddpm.BackBufferFormat = D3DFMT_A8R8G8B8;
	ddpm.BackBufferCount = 1;
	ddpm.MultiSampleType = D3DMULTISAMPLE_NONE;
	ddpm.MultiSampleQuality = 0;
	ddpm.SwapEffect = D3DSWAPEFFECT_DISCARD;
	ddpm.hDeviceWindow = m_hWnd;
	ddpm.Windowed = TRUE;
	ddpm.EnableAutoDepthStencil = TRUE;
	ddpm.AutoDepthStencilFormat = D3DFMT_D24S8;
	ddpm.Flags = 0;
	ddpm.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	ddpm.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, nVertexProcessing, &ddpm, &m_pD3Dev9);

	do 
	{
		if(FAILED(hr))
		{
			LOG(WARNING) << "Not support D3DFMT_D24S8 stencil format, trying to use D3DFMT_D16";

			ddpm.AutoDepthStencilFormat = D3DFMT_D16;

			hr = pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, nVertexProcessing, &ddpm, &m_pD3Dev9);

			if(FAILED(hr))
			{
				LOG(ERROR) << "IDirect3D9::CreateDevice failed";
				MSGBOX_ERR("IDirect3D9::CreateDevice failed");
				break;
			}
		}
	} while (0);

	pD3D9->Release();
	pD3D9 = NULL;

	if(FAILED(hr))
	{
		return S_FALSE;
	}

	if(OnEnvCreate())
	{
		return S_OK;
	}
	return S_FALSE;
}

void SRRenderWnd::UnInitD3D9()
{
	SSAFE_RELEASE(m_pD3Dev9);
}

void SRRenderWnd::ShowWindow(bool bShow /* = true */)
{
	if(0 == m_hWnd)
	{
		return;
	}

	::ShowWindow(m_hWnd, bShow ? SW_NORMAL : SW_HIDE);
}

bool SRRenderWnd::OnCreate(LPCREATESTRUCT _pCreateStruct, LRESULT& _lRet)
{
	return false;
}

bool SRRenderWnd::OnLButtonDown(UINT _uFlag, const POINT& _ptPos, LRESULT& _lRet)
{
	return false;
}

bool SRRenderWnd::OnClose(LRESULT& _lRet)
{
	return false;
}

bool SRRenderWnd::OnDestroy(LRESULT& _lRet)
{
	OnEnvDestroy();
	UnInitD3D9();

	_lRet = 0;
	m_hWnd = 0;

	if(SRRenderApp::GetInstancePtr()->GetRenderWnd() == this)
	{
		SRRenderApp::GetInstancePtr()->SetRenderWnd(NULL);
		LOG(INFO) << "Main render window destroyed...";
	}

	PostQuitMessage(0);
	return true;
}

//IDirect3DVertexBuffer9* SRRenderWnd::Gfx_CreateVertexBuffer(DWORD _dwVertexSum, DWORD _dwUsage /* = D3DUSAGE_WRITEONLY */, D3DPOOL _ePool /* = D3DPOOL_MANAGED */)
/*
{
	if(NULL == m_pD3Dev9)
	{
		return false;
	}
	
	IDirect3DVertexBuffer9* pVertexBuf = NULL;

	HRESULT hr = m_pD3Dev9->CreateVertexBuffer(sizeof(SRVertex) * _dwVertexSum,
		_dwUsage,
		SRVertex::FVF,
		_ePool,
		&pVertexBuf,
		NULL);

	if(D3D_OK == hr)
	{
		return pVertexBuf;
	}

	return NULL;
}*/

IDirect3DIndexBuffer9* SRRenderWnd::Gfx_CreateIndexBuffer(DWORD _dwIndexSum, DWORD _dwUsage /* = D3DUSAGE_WRITEONLY */, D3DPOOL _ePool /* = D3DPOOL_MANAGED */, D3DFORMAT _eFormat /* = D3DFMT_INDEX16 */)
{
	if(NULL == m_pD3Dev9)
	{
		return false;
	}
	
	IDirect3DIndexBuffer9* pIndexBuf = NULL;

	UINT uLength = sizeof(WORD);
	if(D3DFMT_INDEX32 == _eFormat)
	{
		uLength = sizeof(DWORD);
	}

	HRESULT hr = m_pD3Dev9->CreateIndexBuffer(_dwIndexSum * uLength,
		_dwUsage,
		_eFormat,
		_ePool,
		&pIndexBuf,
		NULL);

	if(D3D_OK == hr)
	{
		return pIndexBuf;
	}

	return NULL;
}

bool SRRenderWnd::Gfx_SetViewTransform(const D3DXVECTOR3* _pPosition /* = NULL */, const D3DXVECTOR3* _pTarget /* = NULL */, const D3DXVECTOR3* _pUp /* = NULL */)
{
	if(NULL == m_pD3Dev9)
	{
		return false;
	}

	D3DXVECTOR3 pos(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	if(NULL != _pPosition)
	{
		pos = *_pPosition;
	}
	if(NULL != _pTarget)
	{
		target = *_pTarget;
	}
	if(NULL != _pUp)
	{
		up = *_pUp;
	}

	D3DXMATRIX trans;
	D3DXMatrixLookAtLH(&trans, &pos, &target, &up);

	HRESULT hr = m_pD3Dev9->SetTransform(D3DTS_VIEW, &trans);

	if(D3D_OK == hr)
	{
		return true;
	}
	return false;
}

bool SRRenderWnd::Gfx_SetProjectionTransform(float _fFovy /* = D3DX_PI * 0.5f */, float _fZn /* = 1.0f */, float _fZf /* = 1000.0f */)
{
	float fAspect = float(m_rcWnd.right - m_rcWnd.left) / float(m_rcWnd.bottom - m_rcWnd.top);
	D3DXMATRIX proj;

	D3DXMatrixPerspectiveFovLH(&proj,
		_fFovy,
		fAspect,
		_fZn,
		_fZf);

	HRESULT hr = m_pD3Dev9->SetTransform(D3DTS_PROJECTION, &proj);

	if(D3D_OK == hr)
	{
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////
//	static
LRESULT SRRenderWnd::_WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	SRRenderWnd* pRenderWnd = SRRenderApp::GetInstancePtr()->GetRenderWnd();
	if(NULL == pRenderWnd)
	{
		return ::DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
	}
	if(pRenderWnd->GetHWND() != _hWnd)
	{
		return ::DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
	}

	bool bHandled = false;
	LRESULT lRet = 0;

	switch(_uMsg)
	{
	case WM_CREATE:
		{
			bHandled = pRenderWnd->OnCreate((LPCREATESTRUCT)_wParam, lRet);
		}break;
	case WM_LBUTTONDOWN:
		{
			UINT uFlag = (UINT)_wParam;
			POINT ptPos = {GET_X_LPARAM(_lParam), GET_Y_LPARAM(_lParam)};
			bHandled = pRenderWnd->OnLButtonDown(uFlag, ptPos, lRet);
		}break;
	case WM_CLOSE:
		{
			bHandled = pRenderWnd->OnClose(lRet);
		}break;
	case WM_DESTROY:
		{
			bHandled = pRenderWnd->OnDestroy(lRet);
		}break;
	}

	if(!bHandled)
	{
		lRet = ::DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
	}

	return lRet;
}