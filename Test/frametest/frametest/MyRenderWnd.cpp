#include "stdafx.h"
#include "MyRenderWnd.h"
#include <core/SRRenderApp.h>
#include <util/SRLogger.h>
//////////////////////////////////////////////////////////////////////////
bool CMyListener::OnMessage(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	if(_uMsg == WM_LBUTTONDOWN)
	{
		LOG(ERROR) << "Click";
		printf("Click");
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////
void CMyRenderWnd::OnDrawFrame()
{

}

bool CMyRenderWnd::OnEnvCreate()
{
	CMyListener* pListener = new CMyListener;
	SRRenderApp::GetInstancePtr()->AddMsgListener(pListener);

	return true;
}