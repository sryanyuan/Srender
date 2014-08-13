#ifndef _INC_COLORTRIANGLE_
#define _INC_COLORTRIANGLE_
//////////////////////////////////////////////////////////////////////////
#include <core/SRRenderWnd.h>
#include <core/SRVertex.h>
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
class ColorTriangleWnd : public SRRenderWnd
{
public:
	ColorTriangleWnd();
	virtual ~ColorTriangleWnd();

public:
	virtual bool OnEnvCreate();
	virtual void OnEnvDestroy();
	virtual void OnDrawFrame();

public:
	static int AppMain(HINSTANCE _hInstance)
	{
		return AppTemplate_Main<ColorTriangleWnd>(_hInstance, "ColorTriangle");
	}

protected:
	IDirect3DVertexBuffer9* m_pVertexBuf;
	ID3DXFont* m_pFont;
};
//////////////////////////////////////////////////////////////////////////
#endif