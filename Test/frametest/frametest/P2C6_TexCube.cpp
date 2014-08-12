#include "stdafx.h"
#include "P2C6_TexCube.h"
#include <core/SRColor.h>
#include <Shlwapi.h>
//////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "shlwapi.lib")
//////////////////////////////////////////////////////////////////////////
bool IsKeyPressed(int _nVK)
{
	if(GetAsyncKeyState(_nVK) & 0x8000)
	{
		return true;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////
//	TexCube
TexCube::TexCube()
{
	m_pIB = NULL;
	m_pVB = NULL;
	m_pWnd = NULL;
}

TexCube::~TexCube()
{
	Release();
}


bool TexCube::Create(SRRenderWnd* _pWnd)
{
	m_pWnd = _pWnd;

	IDirect3DDevice9* pDev = m_pWnd->GetD3DDevice();

	m_pVB = m_pWnd->Gfx_CreateVertexBuffer<SRNormalTextureVertex>(24);
	m_pIB = m_pWnd->Gfx_CreateIndexBuffer(36);

	WORD* pIndex = NULL;
	SRNormalTextureVertex* pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	//	front
	pVertex[0] = SRNormalTextureVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	pVertex[1] = SRNormalTextureVertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	pVertex[2] = SRNormalTextureVertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	pVertex[3] = SRNormalTextureVertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;

	pIndex[3] = 0;
	pIndex[4] = 2;
	pIndex[5] = 3;

	//	back
	pVertex[4] = SRNormalTextureVertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	pVertex[5] = SRNormalTextureVertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	pVertex[6] = SRNormalTextureVertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	pVertex[7] = SRNormalTextureVertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);

	pIndex[6] = 7;
	pIndex[7] = 6;
	pIndex[8] = 4;

	pIndex[9] = 4;
	pIndex[10] = 6;
	pIndex[11] = 5;

	//	left side
	pVertex[8] = SRNormalTextureVertex(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	pVertex[9] = SRNormalTextureVertex(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pVertex[10] = SRNormalTextureVertex(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	pVertex[11] = SRNormalTextureVertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	pIndex[12] = 8;
	pIndex[13] = 9;
	pIndex[14] = 10;

	pIndex[15] = 8;
	pIndex[16] = 10;
	pIndex[17] = 11;

	//	right side
	pVertex[12] = SRNormalTextureVertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	pVertex[13] = SRNormalTextureVertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	pVertex[14] = SRNormalTextureVertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pVertex[15] = SRNormalTextureVertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	pIndex[18] = 15;
	pIndex[19] = 14;
	pIndex[20] = 13;

	pIndex[21] = 15;
	pIndex[22] = 13;
	pIndex[23] = 12;

	//	top side
	pVertex[16] = SRNormalTextureVertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[17] = SRNormalTextureVertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	pVertex[18] = SRNormalTextureVertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	pVertex[19] = SRNormalTextureVertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	pIndex[24] = 16;
	pIndex[25] = 17;
	pIndex[26] = 18;

	pIndex[27] = 16;
	pIndex[28] = 18;
	pIndex[29] = 19;

	//	bottom side
	pVertex[20] = SRNormalTextureVertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	pVertex[21] = SRNormalTextureVertex(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	pVertex[22] = SRNormalTextureVertex(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	pVertex[23] = SRNormalTextureVertex(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);

	pIndex[30] = 23;
	pIndex[31] = 22;
	pIndex[32] = 21;

	pIndex[33] = 23;
	pIndex[34] = 21;
	pIndex[35] = 20;

	m_pIB->Unlock();
	m_pVB->Unlock();

	return true;
}

void TexCube::Release()
{
	m_pWnd = NULL;

	SSAFE_RELEASE(m_pVB);
	SSAFE_RELEASE(m_pIB);
}

void TexCube::Render()
{
	if(NULL == m_pWnd ||
		NULL == m_pVB ||
		NULL == m_pIB)
	{
		return;
	}

	IDirect3DDevice9* pDev = m_pWnd->GetD3DDevice();

	pDev->SetStreamSource(0, m_pVB, 0, sizeof(SRNormalTextureVertex));
	pDev->SetFVF(SRNormalTextureVertex::FVF);
	pDev->SetIndices(m_pIB);

	pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}


//////////////////////////////////////////////////////////////////////////
//	TexCubeWnd
TexCubeWnd::TexCubeWnd()
{
	m_pTex = NULL;
}

TexCubeWnd::~TexCubeWnd()
{

}

bool TexCubeWnd::OnEnvCreate()
{
	if(!m_xCube.Create(this))
	{
		return false;
	}

	D3DLIGHT9 lgt;
	ZeroMemory(&lgt, sizeof(lgt));
	lgt.Type = D3DLIGHT_DIRECTIONAL;
	lgt.Ambient   = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	lgt.Diffuse   = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lgt.Specular  = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	lgt.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	m_pD3Dev9->SetLight(0, &lgt);
	m_pD3Dev9->LightEnable(0, TRUE);

	m_pD3Dev9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	char szTexturePath[MAX_PATH] = {0};
	GetModuleFileName(NULL, szTexturePath, sizeof(szTexturePath));
	PathRemoveFileSpec(szTexturePath);
	strcat(szTexturePath, "\\res\\p2c6_tex01.jpg");

	if(!PathFileExists(szTexturePath))
	{
		MessageBox(NULL, "Cannot load texture...", "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	HRESULT hr = D3DXCreateTextureFromFile(m_pD3Dev9, szTexturePath, &m_pTex);
	if(D3D_OK != hr ||
		NULL == m_pTex)
	{
		return false;
	}

	D3DXVECTOR3 pos(0.0f, 0.0f, -4.0f);
	Gfx_SetViewTransform(&pos);
	Gfx_SetProjectionTransform();

	return true;
}

void TexCubeWnd::OnEnvDestroy()
{
	m_xCube.Release();
	SSAFE_RELEASE(m_pTex);
}

void TexCubeWnd::OnDrawFrame()
{
	//////////////////////////////////////////////////////////////////////////
	//	calculate
	static float s_fRotateX = 0.0f;
	static float s_fRotateY = 0.0f;
	static float s_fRotateZ = 0.0f;

	static float s_fTranslateZ = 0.0f;
	static float s_fTranslateX = 0.0f;

	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();
	float dt = pApp->GetTimeDelta();

	if(IsKeyPressed(VK_LEFT))
	{
		s_fRotateY += dt * 5.0f;
	}
	if(IsKeyPressed(VK_RIGHT))
	{
		s_fRotateY -= dt * 5.0f;
	}
	if(IsKeyPressed(VK_UP))
	{
		s_fRotateX += dt * 5.0f;
	}
	if(IsKeyPressed(VK_DOWN))
	{
		s_fRotateX -= dt * 5.0f;
	}
	if(IsKeyPressed('A'))
	{
		s_fTranslateX -= dt * 5.0f;
	}
	if(IsKeyPressed('D'))
	{
		s_fTranslateX += dt * 5.0f;
	}
	if(IsKeyPressed('W'))
	{
		s_fTranslateZ += dt * 5.0f;
	}
	if(IsKeyPressed('S'))
	{
		s_fTranslateZ -= dt * 5.0f;
	}

	while(s_fRotateY > 6.28f)
	{
		s_fRotateY -= 6.28f;
	}
	while(s_fRotateY < 0)
	{
		s_fRotateY += 6.28f;
	}
	while(s_fRotateX > 6.28f)
	{
		s_fRotateX -= 6.28f;
	}
	while(s_fRotateX < 0)
	{
		s_fRotateX += 6.28f;
	}

	D3DXMATRIX roty;
	D3DXMatrixRotationY(&roty, s_fRotateY);

	D3DXMATRIX rotx;
	D3DXMatrixRotationX(&rotx, s_fRotateX);

	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, s_fTranslateX, 0.0f, s_fTranslateZ);

	D3DXMATRIX rot = rotx * roty;

	D3DXMATRIX world = rot * trans;
	m_pD3Dev9->SetTransform(D3DTS_WORLD, &world);

	//////////////////////////////////////////////////////////////////////////
	//	render
	m_pD3Dev9->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	D3DMATERIAL9 mtrl;
	mtrl.Ambient = SRColor::GetCommonColor(SRColor::CC_WHITE);
	mtrl.Diffuse = SRColor::GetCommonColor(SRColor::CC_WHITE);
	mtrl.Specular = SRColor::GetCommonColor(SRColor::CC_WHITE);
	mtrl.Emissive = SRColor::GetCommonColor(SRColor::CC_BLACK);
	mtrl.Power = 2.0f;

	m_pD3Dev9->SetMaterial(&mtrl);
	m_pD3Dev9->SetTexture(0, m_pTex);

	m_xCube.Render();

	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}