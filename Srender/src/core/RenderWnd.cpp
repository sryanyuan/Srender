#include <core/RenderWnd.h>
#include <core/RenderApp.h>
#include <util/debug.h>
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
			return false;
		}
	}

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

	SRRenderApp::GetInstancePtr()->SetRenderWnd(this);

	return true;
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
	_lRet = 0;
	m_hWnd = 0;
	PostQuitMessage(0);
	return true;
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