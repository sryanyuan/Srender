#include "stdafx.h"
#include "P2C7_MaterialAlpha.h"
#include <core/SRColor.h>
#include <Shlwapi.h>
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
	//	title
	SetWindowText(GetHWND(), "MaterialAlpha");

	//	texture
	//char sz

	//	vertex
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
	
}