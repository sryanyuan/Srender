#ifndef _INC_TEXALPHA_
#define _INC_TEXALPHA_
//////////////////////////////////////////////////////////////////////////
#include <core/SRRenderWnd.h>
#include <core/SRVertex.h>
#include <util/SRLogger.h>
#include <util/debug.h>
#include "P2C6_TexCube.h"
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
class TexAlphaWnd : public SRRenderWnd, public AppMainEntry<TexAlphaWnd>
{
public:
	TexAlphaWnd();
	virtual ~TexAlphaWnd();

public:
	bool OnEnvCreate();
	void OnEnvDestroy();
	void OnDrawFrame();

protected:
	IDirect3DVertexBuffer9* m_pVB;
	TexCube m_xCube;
	IDirect3DTexture9* m_pTexQuad;
	IDirect3DTexture9* m_pTexCube;
};
//////////////////////////////////////////////////////////////////////////
#endif