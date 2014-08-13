#ifndef _INC_P2C7_MATERIALALPHA_
#define _INC_P2C7_MATERIALALPHA_
//////////////////////////////////////////////////////////////////////////
#include <core/RenderWnd.h>
#include <core/SRVertex.h>
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
class MaterialAlphaWnd : public SRRenderWnd, public AppMainEntry<MaterialAlphaWnd>
{
public:
	MaterialAlphaWnd();
	virtual ~MaterialAlphaWnd();

public:
	virtual bool OnEnvCreate();
	virtual void OnEnvDestroy();
	virtual void OnDrawFrame();

public:
	//	for background
	D3DMATERIAL9 m_stMaterialBackGround;
	IDirect3DVertexBuffer9* m_pVB;
	IDirect3DTexture9* m_pTex;

	//	for teapot mesh
	ID3DXMesh* m_pMeshTeapot;
	D3DMATERIAL9 m_stMaterialTeapot;
};
//////////////////////////////////////////////////////////////////////////
#endif