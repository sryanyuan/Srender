#include "stdafx.h"
#include "P2C7_MaterialAlpha.h"
#include <core/SRColor.h>
#include <Shlwapi.h>
#include <util/debug.h>
//////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "shlwapi.lib")
//////////////////////////////////////////////////////////////////////////
MaterialAlphaWnd::MaterialAlphaWnd()
{
	m_pTex = NULL;
	m_pVB = NULL;
	m_pMeshTeapot = NULL;

	ZeroMemory(&m_stMaterialBackGround, sizeof(D3DMATERIAL9));
	ZeroMemory(&m_stMaterialTeapot, sizeof(D3DMATERIAL9));
}

MaterialAlphaWnd::~MaterialAlphaWnd()
{

}


bool MaterialAlphaWnd::OnEnvCreate()
{
	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();

	//	title
	SetWindowText(GetHWND(), "MaterialAlpha");

	//	texture
	SRTrace("Load texture...");

	char szTexturePath[MAX_PATH] = {0};
	sprintf(szTexturePath, "%s\\res\\p2c6_tex01.jpg", pApp->GetWorkingDir());
	if(!PathFileExists(szTexturePath))
	{
		return false;
	}
	HRESULT hr = D3DXCreateTextureFromFile(m_pD3Dev9,
		szTexturePath,
		&m_pTex);
	if(D3D_OK != hr ||
		NULL == m_pTex)
	{
		return false;
	}

	m_pD3Dev9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3Dev9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3Dev9->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT); 

	//	vertex
	SRTrace("Create vertex...");

	m_pVB = Gfx_CreateVertexBuffer<SRNormalTextureVertex>(6);
	if(NULL == m_pVB)
	{
		return false;
	}

	SRNormalTextureVertex* pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = SRNormalTextureVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[1] = SRNormalTextureVertex(-10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pVertex[2] = SRNormalTextureVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	pVertex[3] = SRNormalTextureVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[4] = SRNormalTextureVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	pVertex[5] = SRNormalTextureVertex(10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	m_pVB->Unlock();

	m_stMaterialBackGround.Ambient = SRColor::GetCommonColor(SRColor::CC_WHITE);
	m_stMaterialBackGround.Diffuse = SRColor::GetCommonColor(SRColor::CC_WHITE);
	m_stMaterialBackGround.Specular = SRColor::GetCommonColor(SRColor::CC_WHITE);
	m_stMaterialBackGround.Emissive = SRColor::GetCommonColor(SRColor::CC_BLACK);
	m_stMaterialBackGround.Power = 2.0f;

	//	light
	SRTrace("Set light...");

	D3DLIGHT9 lgt;
	ZeroMemory(&lgt, sizeof(D3DLIGHT9));
	lgt.Type = D3DLIGHT_DIRECTIONAL;
	lgt.Diffuse = SRColor::GetCommonColor(SRColor::CC_WHITE);
	lgt.Specular = SRColor::GetCommonColor(SRColor::CC_WHITE) * 0.2f;
	lgt.Ambient = SRColor::GetCommonColor(SRColor::CC_WHITE) * 0.6f;
	lgt.Direction = D3DXVECTOR3(0.707f, 0.0f, 0.707f);
	m_pD3Dev9->SetLight(0, &lgt);
	m_pD3Dev9->LightEnable(0, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	//	teapot
	hr = D3DXCreateTeapot(m_pD3Dev9, &m_pMeshTeapot, NULL);
	if(D3D_OK != hr ||
		NULL == m_pMeshTeapot)
	{
		return false;
	}

	m_stMaterialTeapot.Ambient = SRColor::GetCommonColor(SRColor::CC_RED);
	m_stMaterialTeapot.Diffuse = SRColor::GetCommonColor(SRColor::CC_RED);
	m_stMaterialTeapot.Specular = SRColor::GetCommonColor(SRColor::CC_RED);
	m_stMaterialTeapot.Emissive = SRColor::GetCommonColor(SRColor::CC_BLACK);
	m_stMaterialTeapot.Diffuse.a = 0.5f;
	m_stMaterialTeapot.Power = 2.0f;

	m_pD3Dev9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	m_pD3Dev9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	m_pD3Dev9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3Dev9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//	view matrix
	D3DXVECTOR3 pos(0.0f, 0.0f, -5.0f);
	Gfx_SetViewTransform(&pos);

	//	projection matrix
	Gfx_SetProjectionTransform();

	return true;
}

void MaterialAlphaWnd::OnEnvDestroy()
{
	SSAFE_RELEASE(m_pTex);
	SSAFE_RELEASE(m_pVB);
	SSAFE_RELEASE(m_pMeshTeapot);
}

void MaterialAlphaWnd::OnDrawFrame()
{
	//////////////////////////////////////////////////////////////////////////
	//	calc
	if(Input_IsKeyPressed('A'))
	{
		m_stMaterialTeapot.Diffuse.a -= 0.01f;
	}
	if(Input_IsKeyPressed('D'))
	{
		m_stMaterialTeapot.Diffuse.a += 0.01f;
	}
	if(m_stMaterialTeapot.Diffuse.a > 1.0f)
	{
		m_stMaterialTeapot.Diffuse.a = 1.0f;
	}
	if(m_stMaterialTeapot.Diffuse.a < 0.0f)
	{
		m_stMaterialTeapot.Diffuse.a = 0.0f;
	}

	//////////////////////////////////////////////////////////////////////////
	//	render
	m_pD3Dev9->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	//	back to the original world matrix state
	D3DXMATRIX mOriginal;
	D3DXMatrixIdentity(&mOriginal);
	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mOriginal);

	m_pD3Dev9->SetTexture(0, m_pTex);
	m_pD3Dev9->SetMaterial(&m_stMaterialBackGround);
	m_pD3Dev9->SetStreamSource(0, m_pVB, 0, sizeof(SRNormalTextureVertex));
	m_pD3Dev9->SetFVF(SRNormalTextureVertex::FVF);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, 1.5f, 1.5f, 1.5f);
	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mScale);
	m_pD3Dev9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3Dev9->SetTexture(0, 0);
	m_pD3Dev9->SetMaterial(&m_stMaterialTeapot);
	m_pMeshTeapot->DrawSubset(0);
	m_pD3Dev9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}