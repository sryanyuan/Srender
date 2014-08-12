#include "stdafx.h"
#include "P2C6_TexQuad.h"
#include <Shlwapi.h>
//////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "shlwapi.lib")
//////////////////////////////////////////////////////////////////////////
TexQuadWnd::TexQuadWnd()
{
	m_pTex = NULL;
	m_pVB = NULL;
}

TexQuadWnd::~TexQuadWnd()
{

}


bool TexQuadWnd::OnEnvCreate()
{
	m_pVB = Gfx_CreateVertexBuffer<SRNormalTextureVertex>(6);

	if(NULL == m_pVB)
	{
		return false;
	}

	SRNormalTextureVertex* pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = SRNormalTextureVertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[1] = SRNormalTextureVertex(-1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pVertex[2] = SRNormalTextureVertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	pVertex[3] = SRNormalTextureVertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[4] = SRNormalTextureVertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	pVertex[5] = SRNormalTextureVertex(1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	m_pVB->Unlock();

	char szTexturePath[MAX_PATH] = {0};
	GetModuleFileName(NULL, szTexturePath, sizeof(szTexturePath));
	PathRemoveFileSpec(szTexturePath);
	strcat(szTexturePath, "\\res\\p2c6_tex00.bmp");

	if(!PathFileExists(szTexturePath))
	{
		MessageBox(NULL, "Cannot load resource file...", "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	HRESULT hr = D3DXCreateTextureFromFile(m_pD3Dev9, szTexturePath, &m_pTex);
	if(D3D_OK != hr ||
		NULL == m_pTex)
	{
		return false;
	}

	m_pD3Dev9->SetTexture(0, m_pTex);

	m_pD3Dev9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3Dev9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3Dev9->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT); 

	m_pD3Dev9->SetRenderState(D3DRS_LIGHTING, FALSE);
	Gfx_SetProjectionTransform();

	D3DXVECTOR3 pos(0.0f, 0.0f, -3.0f);
	Gfx_SetViewTransform(&pos);

	return true;
}

void TexQuadWnd::OnEnvDestroy()
{
	SSAFE_RELEASE(m_pTex);
	SSAFE_RELEASE(m_pVB);
}

void TexQuadWnd::OnDrawFrame()
{
	m_pD3Dev9->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	m_pD3Dev9->SetStreamSource(0, m_pVB, 0, sizeof(SRNormalTextureVertex));
	m_pD3Dev9->SetFVF(SRNormalTextureVertex::FVF);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);

	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}