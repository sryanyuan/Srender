#include "stdafx.h"
#include "P2C7_TexAlpha.h"
#include <core/SRRenderApp.h>
//////////////////////////////////////////////////////////////////////////
TexAlphaWnd::TexAlphaWnd()
{
	m_pTexCube = m_pTexQuad = NULL;
}

TexAlphaWnd::~TexAlphaWnd()
{

}


bool TexAlphaWnd::OnEnvCreate()
{
	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();

	SetWindowText(GetHWND(), "TexAlpha");

	char szTexturePath[MAX_PATH] = {0};
	sprintf(szTexturePath, "%s\\res\\lobbyxpos.jpg", pApp->GetWorkingDir());
	if(!PathFileExists(szTexturePath))
	{
		SRTrace("[%s] not exists...", szTexturePath);
		return false;
	}

	HRESULT hr = D3DXCreateTextureFromFile(m_pD3Dev9, szTexturePath, &m_pTexQuad);
	if(D3D_OK != hr ||
		NULL == m_pTexQuad)
	{
		return false;
	}

	sprintf(szTexturePath, "%s\\res\\cratewalpha.dds", pApp->GetWorkingDir());
	if(!PathFileExists(szTexturePath))
	{
		SRTrace("[%s] not exists...", szTexturePath);
		return false;
	}
	hr = D3DXCreateTextureFromFile(m_pD3Dev9, szTexturePath, &m_pTexCube);
	if(D3D_OK != hr ||
		NULL == m_pTexCube)
	{
		return false;
	}

	Gfx_SetSamplerFilter();

	if(!m_xCube.Create(this))
	{
		return false;
	}

	m_pVB = Gfx_CreateVertexBuffer<SRNormalTextureVertex>(6);

	SRNormalTextureVertex* pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = SRNormalTextureVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[1] = SRNormalTextureVertex(-10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pVertex[2] = SRNormalTextureVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	pVertex[3] = SRNormalTextureVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[4] = SRNormalTextureVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	pVertex[5] = SRNormalTextureVertex(10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	m_pVB->Unlock();


	m_pD3Dev9->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	alpha
	m_pD3Dev9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3Dev9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	m_pD3Dev9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3Dev9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DXVECTOR3 vPos(0.0f, 0.0f, -2.5f);
	Gfx_SetViewTransform(&vPos);
	Gfx_SetProjectionTransform();

	return true;
}

void TexAlphaWnd::OnEnvDestroy()
{
	SSAFE_RELEASE(m_pVB);
	m_xCube.Release();
	SSAFE_RELEASE(m_pTexQuad);
	SSAFE_RELEASE(m_pTexCube);
}

void TexAlphaWnd::OnDrawFrame()
{
	static float s_fRotateX = 0.0f;
	static float s_fRotateY = 0.0f;

	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();
	float dt = pApp->GetTimeDelta();

	D3DXMATRIX mRotX;
	s_fRotateX += dt;
	if(s_fRotateX >= 6.28f)
	{
		s_fRotateX = 0.0f;
	}
	D3DXMatrixRotationX(&mRotX, s_fRotateX);

	D3DXMATRIX mRotY;
	s_fRotateY += dt * 1.5f;
	if(s_fRotateY >= 6.28f)
	{
		s_fRotateY = 0.0f;
	}
	D3DXMatrixRotationY(&mRotY, s_fRotateY);

	D3DXMATRIX mRot = mRotX * mRotY;
	//////////////////////////////////////////////////////////////////////////
	m_pD3Dev9->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	D3DXMATRIX mIdentity;
	D3DXMatrixIdentity(&mIdentity);
	m_pD3Dev9->SetTexture(0, m_pTexQuad);
	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mIdentity);
	m_pD3Dev9->SetStreamSource(0, m_pVB, 0, sizeof(SRNormalTextureVertex));
	m_pD3Dev9->SetFVF(SRNormalTextureVertex::FVF);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mRot);
	m_pD3Dev9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3Dev9->SetTexture(0, m_pTexCube);
	m_xCube.Render();
	m_pD3Dev9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}