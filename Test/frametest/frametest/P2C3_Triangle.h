#ifndef _INC_P2C3_TRIANGLE_
#define _INC_P2C3_TRIANGLE_
//////////////////////////////////////////////////////////////////////////
#include <core/SRRenderWnd.h>
//////////////////////////////////////////////////////////////////////////
class TriangleWnd : public SRRenderWnd
{
public:
	TriangleWnd();
	virtual ~TriangleWnd();

public:
	virtual void OnDrawFrame();
	virtual bool OnEnvCreate();
	virtual void OnEnvDestroy();

public:
	static int AppMain(HINSTANCE _hInstance);

protected:
	IDirect3DVertexBuffer9* m_pVertexBuf;
};
//////////////////////////////////////////////////////////////////////////
#endif