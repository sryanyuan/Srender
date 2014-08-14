#include "stdafx.h"
#include "P2C8_StencilMirror.h"
#include <core/SIMessageListener.h>
//////////////////////////////////////////////////////////////////////////
class MsgFilter : public SIMessageListener
{
public:
	MsgFilter()
	{
		m_pAttachedWnd = NULL;
	}
	void SetAttachedWnd(StencilMirrorWnd* _pWnd)
	{
		m_pAttachedWnd = _pWnd;
	}

	virtual bool OnMessage(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
	{
		if(WM_MOUSEWHEEL == _uMsg)
		{
			WORD wRotate = HIWORD(_wParam);
			short sRotate = (short)wRotate;
			bool bBack = true;

			if(sRotate > 0)
			{
				bBack = false;
			}

			if(m_pAttachedWnd)
			{
				m_pAttachedWnd->OnMouseWheel(bBack);
			}
		}

		return false;
	}

protected:
	StencilMirrorWnd* m_pAttachedWnd;
};
//////////////////////////////////////////////////////////////////////////
StencilMirrorWnd::StencilMirrorWnd()
{
	m_pVB = NULL;

	m_pTexFloor = m_pTexMirror = m_pTexWall = NULL;

	m_pMeshTeapot = NULL;

	ZeroMemory(&m_stMaterialFloor, sizeof(D3DMATERIAL9));
	ZeroMemory(&m_stMaterialWall, sizeof(D3DMATERIAL9));
	ZeroMemory(&m_stMaterialMirror, sizeof(D3DMATERIAL9));
	ZeroMemory(&m_stMaterialTeapot, sizeof(D3DMATERIAL9));

	m_stVectorTeapot.x = 0.0f;
	m_stVectorTeapot.y = 3.0f;
	m_stVectorTeapot.z = -7.5f;

	m_stVectorCamera.x = -10.0f;
	m_stVectorCamera.y = 3.0f;
	m_stVectorCamera.z = -15.0f;
}

StencilMirrorWnd::~StencilMirrorWnd()
{

}                                                                                                                                                                              


void StencilMirrorWnd::OnMouseWheel(bool _bBack)
{
	float fMoveDrt = 1.0f;
	if(_bBack)
	{
		fMoveDrt = -1.0f;
	}
	m_stVectorCamera.z += fMoveDrt;

	Gfx_SetViewTransform(&m_stVectorCamera);
}

bool StencilMirrorWnd::OnEnvCreate()
{
	SetWindowText(GetHWND(), "StencilMirror");

	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();

	MsgFilter* pFilter = new MsgFilter;
	pFilter->SetAttachedWnd(this);
	pApp->AddMsgListener(pFilter);

	//	fill materials
	m_stMaterialFloor.Ambient = SRColor::GetCommonColor(SRColor::CC_WHITE);
	m_stMaterialFloor.Diffuse = SRColor::GetCommonColor(SRColor::CC_WHITE);
	m_stMaterialFloor.Specular = SRColor::GetCommonColor(SRColor::CC_WHITE);
	m_stMaterialFloor.Emissive = SRColor::GetCommonColor(SRColor::CC_BLACK);
	m_stMaterialFloor.Power = 2.0f;

	m_stMaterialMirror = m_stMaterialFloor;
	m_stMaterialWall = m_stMaterialFloor;
	m_stMaterialWall.Specular = 0.2f * SRColor::GetCommonColor(SRColor::CC_WHITE);

	m_stMaterialTeapot.Ambient = SRColor::GetCommonColor(SRColor::CC_YELLOW);
	m_stMaterialTeapot.Diffuse = SRColor::GetCommonColor(SRColor::CC_YELLOW);
	m_stMaterialTeapot.Specular = SRColor::GetCommonColor(SRColor::CC_YELLOW);
	m_stMaterialTeapot.Emissive = SRColor::GetCommonColor(SRColor::CC_BLACK);
	m_stMaterialTeapot.Power = 2.0f;

	HRESULT hr = D3DXCreateTeapot(m_pD3Dev9, &m_pMeshTeapot, NULL);
	if(D3D_OK != hr ||
		NULL == m_pMeshTeapot)
	{
		return false;
	}

	m_pVB = Gfx_CreateVertexBuffer<SRNormalTextureVertex>(24);
	if(NULL == m_pVB)
	{
		return false;
	}

	SRNormalTextureVertex* pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	// floor
	pVertex[0] = SRNormalTextureVertex(-7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[1] = SRNormalTextureVertex(-7.5f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	pVertex[2] = SRNormalTextureVertex( 7.5f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	pVertex[3] = SRNormalTextureVertex(-7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[4] = SRNormalTextureVertex( 7.5f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	pVertex[5] = SRNormalTextureVertex( 7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// wall
	pVertex[6]  = SRNormalTextureVertex(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[7]  = SRNormalTextureVertex(-7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pVertex[8]  = SRNormalTextureVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	pVertex[9]  = SRNormalTextureVertex(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[10] = SRNormalTextureVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	pVertex[11] = SRNormalTextureVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Note: We leave gap in middle of walls for mirror

	pVertex[12] = SRNormalTextureVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[13] = SRNormalTextureVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pVertex[14] = SRNormalTextureVertex(7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	pVertex[15] = SRNormalTextureVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[16] = SRNormalTextureVertex(7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	pVertex[17] = SRNormalTextureVertex(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// mirror
	pVertex[18] = SRNormalTextureVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[19] = SRNormalTextureVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pVertex[20] = SRNormalTextureVertex( 2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	pVertex[21] = SRNormalTextureVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[22] = SRNormalTextureVertex( 2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	pVertex[23] = SRNormalTextureVertex( 2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	m_pVB->Unlock();

	char szTexturePath[MAX_PATH] = {0};
	sprintf(szTexturePath, "%s\\res\\checker.jpg", pApp->GetWorkingDir());
	if(!PathFileExists(szTexturePath))
	{
		return false;
	}

	hr = D3DXCreateTextureFromFile(m_pD3Dev9, szTexturePath, &m_pTexFloor);
	if(D3D_OK != hr ||
		NULL == m_pTexFloor)
	{
		return false;
	}

	sprintf(szTexturePath, "%s\\res\\brick0.jpg", pApp->GetWorkingDir());
	if(!PathFileExists(szTexturePath))
	{
		return false;
	}

	hr = D3DXCreateTextureFromFile(m_pD3Dev9, szTexturePath, &m_pTexWall);
	if(D3D_OK != hr ||
		NULL == m_pTexWall)
	{
		return false;
	}

	sprintf(szTexturePath, "%s\\res\\ice.bmp", pApp->GetWorkingDir());
	if(!PathFileExists(szTexturePath))
	{
		return false;
	}

	hr = D3DXCreateTextureFromFile(m_pD3Dev9, szTexturePath, &m_pTexMirror);
	if(D3D_OK != hr ||
		NULL == m_pTexMirror)
	{
		return false;
	}

	Gfx_SetSamplerFilter();

	//	set light
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = color;
	light.Ambient = color * 0.4f;
	light.Specular = color * 0.6f;
	light.Direction = D3DXVECTOR3(0.707f, -0.707f, 0.707f);

	m_pD3Dev9->SetLight(0, &light);
	m_pD3Dev9->LightEnable(0, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	Gfx_SetViewTransform(&m_stVectorCamera);
	Gfx_SetProjectionTransform(D3DX_PI * 0.25f);

	return true;
}

void StencilMirrorWnd::OnEnvDestroy()
{
	SSAFE_RELEASE(m_pVB);
	SSAFE_RELEASE(m_pTexFloor);
	SSAFE_RELEASE(m_pTexMirror);
	SSAFE_RELEASE(m_pTexWall);
	SSAFE_RELEASE(m_pMeshTeapot);

	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();
	pApp->DestroyMsgListener();
}

void StencilMirrorWnd::OnDrawFrame()
{
	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();
	float dt = pApp->GetTimeDelta();

	//////////////////////////////////////////////////////////////////////////
	//	input
	if(Input_IsKeyPressed(VK_LEFT))
	{
		m_stVectorTeapot.x -= dt * 2.0f;
	}
	if(Input_IsKeyPressed(VK_RIGHT))
	{
		m_stVectorTeapot.x += dt * 2.0f;
	}
	if(Input_IsKeyPressed(VK_UP))
	{
		m_stVectorTeapot.y += dt * 2.0f;
	}
	if(Input_IsKeyPressed(VK_DOWN))
	{
		m_stVectorTeapot.y -= dt * 2.0f;
	}

	//////////////////////////////////////////////////////////////////////////
	m_pD3Dev9->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xff000000, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	//	scene
	m_pD3Dev9->SetMaterial(&m_stMaterialTeapot);
	D3DXMATRIX mTrans;
	D3DXMatrixTranslation(&mTrans, m_stVectorTeapot.x, m_stVectorTeapot.y, m_stVectorTeapot.z);
	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mTrans);
	m_pMeshTeapot->DrawSubset(0);

	D3DXMATRIX mIdentity;
	D3DXMatrixIdentity(&mIdentity);
	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mIdentity);

	m_pD3Dev9->SetStreamSource(0, m_pVB, 0, sizeof(SRNormalTextureVertex));
	m_pD3Dev9->SetFVF(SRNormalTextureVertex::FVF);

	m_pD3Dev9->SetMaterial(&m_stMaterialFloor);
	m_pD3Dev9->SetTexture(0, m_pTexFloor);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	m_pD3Dev9->SetMaterial(&m_stMaterialWall);
	m_pD3Dev9->SetTexture(0, m_pTexWall);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 6, 4);

	m_pD3Dev9->SetMaterial(&m_stMaterialMirror);
	m_pD3Dev9->SetTexture(0, m_pTexMirror);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	//	mirror

	//	1.enable stencil component
	m_pD3Dev9->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILREF, 0x1);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	//	2.disable z-buffer and back-buffer
	m_pD3Dev9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_pD3Dev9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	m_pD3Dev9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	3.draw the mirror region to the stencil buffer
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	//	4.reset the z-buffer and back buffer settings
	m_pD3Dev9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	m_pD3Dev9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	m_pD3Dev9->Clear(0, 0, D3DCLEAR_ZBUFFER, 0xff000000, 1.0f, 0);

	//	5.calculate the mirror matrix
	D3DXMATRIX mMirror;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f);
	D3DXMatrixReflect(&mMirror, &plane);

	//	note: first translate to the teapot position, then reflect it
	mMirror = mTrans * mMirror;

	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mMirror);
	m_pD3Dev9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//	6.draw the teapot in the mirror
	m_pD3Dev9->SetMaterial(&m_stMaterialMirror);
	m_pD3Dev9->SetTexture(0, NULL);
	m_pMeshTeapot->DrawSubset(0);

	//	7.reset settings
	m_pD3Dev9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pD3Dev9->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	m_pD3Dev9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//	present
	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}