// frametest.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "frametest.h"

#include <core/RenderWnd.h>
#include <core/RenderApp.h>
#include <core/MessageListener.h>

#include "MyRenderWnd.h"
#include "P2C3_Cube.h"
#include "P2C3_Triangle.h"
#include "P2C4_ColorTriangle.h"
#include "P2C5_LitPyramid.h"
#include "P2C6_TexQuad.h"
#include "P2C6_TexCube.h"
//////////////////////////////////////////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	//////////////////////////////////////////////////////////////////////////
 	// TODO: �ڴ˷��ô��롣
	//return CubeWnd::AppMain(hInstance);

	//return TriangleWnd::AppMain(hInstance);

	//return ColorTriangleWnd::AppMain(hInstance);

	//return LitPyramid::AppMain(hInstance);

	//return TexQuadWnd::AppMain(hInstance);

	return TexCubeWnd::AppMain(hInstance);
}