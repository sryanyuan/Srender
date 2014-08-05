#ifndef _INC_APPTEMPLATE_
#define _INC_APPTEMPLATE_
//////////////////////////////////////////////////////////////////////////
#include <core/RenderApp.h>
//////////////////////////////////////////////////////////////////////////
template <typename T>
int AppTemplate_Main(HINSTANCE _hInstance)
{
	SRRenderApp::GetInstancePtr()->SetInstance(_hInstance);

	T wnd;
	if(!wnd.Create("P3C3_Cube", 800, 600))
	{
		return -1;
	}

	wnd.ShowWindow();

	return SRRenderApp::GetInstancePtr()->MsgLoop();
}
//////////////////////////////////////////////////////////////////////////
#endif