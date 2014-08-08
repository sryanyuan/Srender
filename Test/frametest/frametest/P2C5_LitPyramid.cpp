#include "stdafx.h"
#include "P2C5_LitPyramid.h"
#include <core/SRColor.h>
//////////////////////////////////////////////////////////////////////////
void CalculateNormal(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _p0, const D3DXVECTOR3* _p1, const D3DXVECTOR3* _p2)
{
	D3DXVECTOR3 u = *_p1 - *_p0;
	D3DXVECTOR3 v = *_p2 - *_p0;

	//	left hand coordinate system...
	D3DXVec3Cross(_pOut, &u, &v);
	D3DXVec3Normalize(_pOut, _pOut);
}
//////////////////////////////////////////////////////////////////////////
LitPyramid::LitPyramid()
{
	m_pVB = NULL;
}

LitPyramid::~LitPyramid()
{

}


bool LitPyramid::OnEnvCreate()
{
	m_pVB = Gfx_CreateVertexBuffer<SRNormalVertex>(4 * 3);
	if(NULL == m_pVB)
	{
		return false;
	}

	SRNormalVertex* pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	//	front side
	D3DXVECTOR3 v0;
	D3DXVECTOR3 v1;
	D3DXVECTOR3 v2;
	D3DXVECTOR3 vn;

	pVertex[0] = SRNormalVertex(-1.0f, 0.0f, -1.0f);
	pVertex[1] = SRNormalVertex(0.0f, 1.0f, 0.0f);
	pVertex[2] = SRNormalVertex(1.0f, 0.0f, -1.0f);

	v0.x = pVertex[0].GetX();
	v0.y = pVertex[0].GetY();
	v0.z = pVertex[0].GetZ();
	v1.x = pVertex[1].GetX();
	v1.y = pVertex[1].GetY();
	v1.z = pVertex[1].GetZ();
	v2.x = pVertex[2].GetX();
	v2.y = pVertex[2].GetY();
	v2.z = pVertex[2].GetZ();
	CalculateNormal(&vn, &v0, &v1, &v2);

	pVertex[0].SetNormalXYZ(vn.x, vn.y, vn.z);
	pVertex[1].SetNormalXYZ(vn.x, vn.y, vn.z);
	pVertex[2].SetNormalXYZ(vn.x, vn.y, vn.z);

	//	left side
	pVertex[3] = SRNormalVertex(-1.0f, 0.0f, 1.0f);
	pVertex[4] = SRNormalVertex(0.0f, 1.0f, 0.0f);
	pVertex[5] = SRNormalVertex(-1.0f, 0.0f, -1.0f);

	v0.x = pVertex[3].GetX();
	v0.y = pVertex[3].GetY();
	v0.z = pVertex[3].GetZ();
	v1.x = pVertex[4].GetX();
	v1.y = pVertex[4].GetY();
	v1.z = pVertex[4].GetZ();
	v2.x = pVertex[5].GetX();
	v2.y = pVertex[5].GetY();
	v2.z = pVertex[5].GetZ();
	CalculateNormal(&vn, &v0, &v1, &v2);

	pVertex[3].SetNormalXYZ(vn.x, vn.y, vn.z);
	pVertex[4].SetNormalXYZ(vn.x, vn.y, vn.z);
	pVertex[5].SetNormalXYZ(vn.x, vn.y, vn.z);

	//	right side
	pVertex[6] = SRNormalVertex(1.0f, 0.0f, -1.0f);
	pVertex[7] = SRNormalVertex(0.0f, 1.0f, 0.0f);
	pVertex[8] = SRNormalVertex(1.0f, 0.0f, 1.0f);

	v0.x = pVertex[6].GetX();
	v0.y = pVertex[6].GetY();
	v0.z = pVertex[6].GetZ();
	v1.x = pVertex[7].GetX();
	v1.y = pVertex[7].GetY();
	v1.z = pVertex[7].GetZ();
	v2.x = pVertex[8].GetX();
	v2.y = pVertex[8].GetY();
	v2.z = pVertex[8].GetZ();
	CalculateNormal(&vn, &v0, &v1, &v2);

	pVertex[6].SetNormalXYZ(vn.x, vn.y, vn.z);
	pVertex[7].SetNormalXYZ(vn.x, vn.y, vn.z);
	pVertex[8].SetNormalXYZ(vn.x, vn.y, vn.z);

	//	back side
	pVertex[9] = SRNormalVertex(1.0f, 0.0f, 1.0f);
	pVertex[10] = SRNormalVertex(0.0f, 1.0f, 0.0f);
	pVertex[11] = SRNormalVertex(-1.0f, 0.0f, 1.0f);

	v0.x = pVertex[9].GetX();
	v0.y = pVertex[9].GetY();
	v0.z = pVertex[9].GetZ();
	v1.x = pVertex[10].GetX();
	v1.y = pVertex[10].GetY();
	v1.z = pVertex[10].GetZ();
	v2.x = pVertex[11].GetX();
	v2.y = pVertex[11].GetY();
	v2.z = pVertex[11].GetZ();
	CalculateNormal(&vn, &v0, &v1, &v2);

	pVertex[9].SetNormalXYZ(vn.x, vn.y, vn.z);
	pVertex[10].SetNormalXYZ(vn.x, vn.y, vn.z);
	pVertex[11].SetNormalXYZ(vn.x, vn.y, vn.z);

	m_pVB->Unlock();

	m_pD3Dev9->SetRenderState(D3DRS_LIGHTING, TRUE);

	D3DMATERIAL9 mtrl;
	mtrl.Ambient = SRColor::GetCommonColor(SRColor::CC_WHITE);
	mtrl.Diffuse = SRColor::GetCommonColor(SRColor::CC_WHITE);
	mtrl.Specular = SRColor::GetCommonColor(SRColor::CC_WHITE);
	mtrl.Emissive = SRColor::GetCommonColor(SRColor::CC_BLACK);
	mtrl.Power = 5.0f;

	m_pD3Dev9->SetMaterial(&mtrl);

	D3DLIGHT9 lgt;
	ZeroMemory(&lgt, sizeof(lgt));
	lgt.Type = D3DLIGHT_DIRECTIONAL;
	lgt.Diffuse = SRColor::GetCommonColor(SRColor::CC_WHITE);
	lgt.Specular = SRColor::GetCommonColor(SRColor::CC_WHITE) * 0.3f;
	lgt.Ambient = SRColor::GetCommonColor(SRColor::CC_WHITE) * 0.6f;
	lgt.Direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_pD3Dev9->SetLight(0, &lgt);
	m_pD3Dev9->LightEnable(0, TRUE);

	m_pD3Dev9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	m_pD3Dev9->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	D3DXVECTOR3 pos(0.0f, 1.0f, -3.0f);
	Gfx_SetViewTransform(&pos);
	Gfx_SetProjectionTransform();

	return true;
}

void LitPyramid::OnEnvDestroy()
{
	SSAFE_RELEASE(m_pVB);
}

void LitPyramid::OnDrawFrame()
{
	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();

	static float s_fRotateY = 0.0f;
	s_fRotateY += pApp->GetTimeDelta();
	static float s_fRotateX = 0.0f;
	s_fRotateX += pApp->GetTimeDelta() * 0.5f;

	D3DXMATRIX roty;
	D3DXMatrixRotationY(&roty, s_fRotateY);

	D3DXMATRIX rotx;
	D3DXMatrixRotationX(&rotx, s_fRotateX);

	D3DXMATRIX rot = rotx * roty;

	if(s_fRotateY > 6.28f)
	{
		s_fRotateY = 0.0f;
	}
	if(s_fRotateX > 6.28f)
	{
		s_fRotateX = 0.0f;
	}

	m_pD3Dev9->SetTransform(D3DTS_WORLD, &roty);

	m_pD3Dev9->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	m_pD3Dev9->SetStreamSource(0, m_pVB, 0, sizeof(SRNormalVertex));
	m_pD3Dev9->SetFVF(SRNormalVertex::FVF);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);

	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}