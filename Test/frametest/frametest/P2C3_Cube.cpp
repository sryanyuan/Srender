#include "stdafx.h"
#include <core/RenderApp.h>
#include "P2C3_Cube.h"
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
int CubeWnd::AppMain(HINSTANCE _hInstance)
{
	return AppTemplate_Main<CubeWnd>(_hInstance);
}
//////////////////////////////////////////////////////////////////////////
CubeWnd::CubeWnd()
{
	m_pIndexBuf = NULL;
	m_pVertexBuf = NULL;
}

CubeWnd::~CubeWnd()
{

}


//////////////////////////////////////////////////////////////////////////
void CubeWnd::OnDrawFrame()
{
	if(NULL == m_pD3Dev9)
	{
		return;
	}
	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();

	//	calculate
	D3DXMATRIX rx, ry;
	D3DXMatrixRotationX(&rx, D3DX_PI / 4.0f);

	static float s_fRotateAngle = 0.0f;
	s_fRotateAngle += pApp->GetTimeDelta();

	D3DXMatrixRotationY(&ry, s_fRotateAngle);
	if(s_fRotateAngle >= D3DX_PI * 2)
	{
		s_fRotateAngle = 0.0f;
	}

	D3DXMATRIX rt;
	rt = rx * ry;
	//m_pD3Dev9->SetTransform(D3DTS_WORLD, &ry);

	//	draw
	m_pD3Dev9->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	m_pD3Dev9->SetStreamSource(0, m_pVertexBuf, 0, sizeof(SRVertex));
	m_pD3Dev9->SetIndices(m_pIndexBuf);
	m_pD3Dev9->SetFVF(SRVertex::FVF);

	//m_pD3Dev9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	m_pD3Dev9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 3, 0, 1);

	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}

bool CubeWnd::OnEnvCreate()
{
	m_pVertexBuf = Gfx_CreateVertexBuffer(8);
	m_pIndexBuf = Gfx_CreateIndexBuffer(36);

	if(NULL == m_pVertexBuf ||
		NULL == m_pIndexBuf)
	{
		return false;
	}

	//	vertex data, 8 vertexs.
	SRVertex* pVertex = NULL;
	m_pVertexBuf->Lock(0, 0, (void**)&pVertex, 0);

	//	z = -1
	pVertex[0].SetXYZ(-1.0f, -1.0f, -1.0f);
	pVertex[1].SetXYZ(-1.0f, 1.0f, -1.0f);
	pVertex[2].SetXYZ(1.0f, 1.0f, -1.0f);
	pVertex[3].SetXYZ(1.0f, -1.0f, -1.0f);

	//	z = 1
	pVertex[4].SetXYZ(-1.0f, -1.0f, 1.0f);
	pVertex[5].SetXYZ(-1.0f, 1.0f, 1.0f);
	pVertex[6].SetXYZ(1.0f, 1.0f, 1.0f);
	pVertex[7].SetXYZ(1.0f, -1.0f, 1.0f);

	m_pVertexBuf->Unlock();

	//	index data.
	WORD* pIndex = NULL;
	m_pIndexBuf->Lock(0, 0, (void**)&pIndex, 0);

	//	triangle 0 , front
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;

	//	triangle 1
	pIndex[3] = 0;
	pIndex[4] = 2;
	pIndex[5] = 3;

	//	triangle 2 , back
	pIndex[6] = 4;
	pIndex[7] = 6;
	pIndex[8] = 5;

	//	triangle 3
	pIndex[9] = 4;
	pIndex[10] = 7;
	pIndex[11] = 6;

	//	triangle 4 , left
	pIndex[12] = 4;
	pIndex[13] = 5;
	pIndex[14] = 1;

	//	triangle 5
	pIndex[15] = 4;
	pIndex[16] = 1;
	pIndex[17] = 0;

	//	triangle 6 , right
	pIndex[18] = 3;
	pIndex[19] = 2;
	pIndex[20] = 6;

	//	triangle 7
	pIndex[21] = 3;
	pIndex[22] = 6;
	pIndex[23] = 7;

	//	triangle 8 , top
	pIndex[24] = 1;
	pIndex[25] = 5;
	pIndex[26] = 6;

	//	triangle 9
	pIndex[27] = 1;
	pIndex[28] = 6;
	pIndex[29] = 2;

	//	triangle 10 , bottom
	pIndex[30] = 4;
	pIndex[31] = 0;
	pIndex[32] = 3;

	//	triangle 11
	pIndex[33] = 4;
	pIndex[34] = 3;
	pIndex[35] = 7;

	m_pIndexBuf->Unlock();

	D3DXVECTOR3 pos(0.0f, 0.0f, -8.0f);
	Gfx_SetViewTransform(&pos);
	Gfx_SetProjectionTransform();

	m_pD3Dev9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return true;
}

void CubeWnd::OnEnvDestroy()
{
	SSAFE_RELEASE(m_pIndexBuf);
	SSAFE_RELEASE(m_pVertexBuf);
}