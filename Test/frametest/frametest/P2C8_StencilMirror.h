#ifndef _INC_P2C8_STENCILMIRRIOR_
#define _INC_P2C8_STENCILMIRRIOR_
//////////////////////////////////////////////////////////////////////////
#include <core/SRRenderWnd.h>
#include <core/SRRenderApp.h>
#include <core/SRVertex.h>
#include <core/SRColor.h>
#include <util/debug.h>
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
class StencilMirrorWnd : public SRRenderWnd , public AppMainEntry<StencilMirrorWnd>
{
public:
	StencilMirrorWnd();
	virtual ~StencilMirrorWnd();

public:
	virtual bool OnEnvCreate();
	virtual void OnEnvDestroy();
	virtual void OnDrawFrame();

	void OnMouseWheel(bool _bBack);

public:
	D3DMATERIAL9 m_stMaterialFloor;
	D3DMATERIAL9 m_stMaterialWall;
	D3DMATERIAL9 m_stMaterialMirror;
	D3DMATERIAL9 m_stMaterialTeapot;

	IDirect3DTexture9* m_pTexFloor;
	IDirect3DTexture9* m_pTexWall;
	IDirect3DTexture9* m_pTexMirror;

	IDirect3DVertexBuffer9* m_pVB;

	ID3DXMesh* m_pMeshTeapot;

	D3DXVECTOR3 m_stVectorTeapot;
	D3DXVECTOR3 m_stVectorCamera;
};
//////////////////////////////////////////////////////////////////////////
#endif