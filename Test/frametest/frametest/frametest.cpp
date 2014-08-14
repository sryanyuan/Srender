// frametest.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "frametest.h"

#include <core/SRRenderWnd.h>
#include <core/SRRenderApp.h>
#include <core/SIMessageListener.h>

#include "MyRenderWnd.h"
#include "P2C3_Cube.h"
#include "P2C3_Triangle.h"
#include "P2C4_ColorTriangle.h"
#include "P2C5_LitPyramid.h"
#include "P2C6_TexQuad.h"
#include "P2C6_TexCube.h"
#include "P2C7_MaterialAlpha.h"
#include "P2C7_TexAlpha.h"
#include "P2C8_StencilMirror.h"
//////////////////////////////////////////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	//////////////////////////////////////////////////////////////////////////
 	// TODO: 在此放置代码。

	//return AppTemplate_Main<CMyRenderWnd>(hInstance, "RenderWndTest");

	//return CubeWnd::AppMain(hInstance);

	//return TriangleWnd::AppMain(hInstance);

	//return ColorTriangleWnd::AppMain(hInstance);

	//return LitPyramid::AppMain(hInstance);

	//return TexQuadWnd::AppMain(hInstance);

	//return TexCubeWnd::AppMain(hInstance);

	//return MaterialAlphaWnd::AppMain(hInstance);

	//return TexAlphaWnd::AppMain(hInstance);

	return StencilMirrorWnd::AppMain(hInstance);
}