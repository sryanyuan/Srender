#ifndef _INC_C3_CUBE_
#define _INC_C3_CUBE_
//////////////////////////////////////////////////////////////////////////
#include <core/RenderWnd.h>
#include <core/SRVertex.h>
//////////////////////////////////////////////////////////////////////////
class CubeWnd : public SRRenderWnd
{
public:
	CubeWnd();
	virtual ~CubeWnd();

public:
	virtual void OnDrawFrame();
	virtual bool OnEnvCreate();
	virtual void OnEnvDestroy();

public:
	static int AppMain(HINSTANCE _hInstance);

protected:
	IDirect3DVertexBuffer9* m_pVertexBuf;
	IDirect3DIndexBuffer9* m_pIndexBuf;
};
//////////////////////////////////////////////////////////////////////////
#endif