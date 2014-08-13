#ifndef _INC_TEXCUBE_
#define _INC_TEXCUBE_
//////////////////////////////////////////////////////////////////////////
#include "core/SRRenderWnd.h"
#include "core/SRVertex.h"
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
//	TexCube
class TexCube
{
public:
	TexCube();
	virtual ~TexCube();

public:
	bool Create(SRRenderWnd* _pWnd);
	void Release();
	void Render();

protected:
	SRRenderWnd* m_pWnd;
	IDirect3DVertexBuffer9* m_pVB;
	IDirect3DIndexBuffer9* m_pIB;
};

//////////////////////////////////////////////////////////////////////////
//	TexCubeWnd
class TexCubeWnd : public SRRenderWnd
{
public:
	TexCubeWnd();
	virtual ~TexCubeWnd();

public:
	virtual bool OnEnvCreate();
	virtual void OnEnvDestroy();
	virtual void OnDrawFrame();

public:
	static int AppMain(HINSTANCE _hInstance)
	{
		return AppTemplate_Main<TexCubeWnd>(_hInstance, "TexCube");
	}

protected:
	TexCube m_xCube;
	IDirect3DTexture9* m_pTex;
};
//////////////////////////////////////////////////////////////////////////
#endif