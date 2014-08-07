#ifndef _INC_LITPYRAMID_
#define _INC_LITPYRAMID_
//////////////////////////////////////////////////////////////////////////
#include <core/RenderWnd.h>
#include <core/SRVertex.h>
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
class LitPyramid : public SRRenderWnd
{
public:
	LitPyramid();
	virtual ~LitPyramid();

public:
	virtual bool OnEnvCreate();
	virtual void OnEnvDestroy();
	virtual void OnDrawFrame();

public:
	static int AppMain(HINSTANCE _hInstance)
	{
		return AppTemplate_Main<LitPyramid>(_hInstance, "LitPyramid");
	}

protected:
	IDirect3DVertexBuffer9* m_pVB;
};
//////////////////////////////////////////////////////////////////////////
#endif