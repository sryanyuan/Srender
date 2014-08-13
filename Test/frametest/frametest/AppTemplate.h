#ifndef _INC_APPTEMPLATE_
#define _INC_APPTEMPLATE_
//////////////////////////////////////////////////////////////////////////
#include <core/SRRenderApp.h>
//////////////////////////////////////////////////////////////////////////
template <typename T>
int AppTemplate_Main(HINSTANCE _hInstance, const char* _pszAppName = "", int _nWndWidth = 800, int _nWndHeight = 600)
{
	SRRenderApp::GetInstancePtr()->SetInstance(_hInstance);

	T wnd;
	if(!wnd.Create(_pszAppName, _nWndWidth, _nWndHeight))
	{
		return -1;
	}

	wnd.ShowWindow();

	return SRRenderApp::GetInstancePtr()->MsgLoop();
}

template <typename T>
class AppMainEntry
{
public:
	static int AppMain(HINSTANCE _hInstance, const char* _pszAppName = "", int _nWndWidth = 800, int _nWndHeight = 600)
	{
		return AppTemplate_Main<T>(_hInstance, _pszAppName, _nWndWidth, _nWndHeight);
	}
};
//////////////////////////////////////////////////////////////////////////
#endif