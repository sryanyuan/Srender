#ifndef _INC_P2C6_TEXQUAD_
#define _INC_P2C6_TEXQUAD_
//////////////////////////////////////////////////////////////////////////
#include <core/RenderWnd.h>
#include <core/SRVertex.h>
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
class TexQuadWnd : public SRRenderWnd
{
public:
	TexQuadWnd();
	virtual ~TexQuadWnd();

public:
	virtual bool OnEnvCreate();
	virtual void OnEnvDestroy();
	virtual void OnDrawFrame();

public:
	static int AppMain(HINSTANCE _hInstance)
	{
		return AppTemplate_Main<TexQuadWnd>(_hInstance, "TexQuad");
	}

protected:
	IDirect3DVertexBuffer9* m_pVB;
	IDirect3DTexture9* m_pTex;
};
//////////////////////////////////////////////////////////////////////////
#endif