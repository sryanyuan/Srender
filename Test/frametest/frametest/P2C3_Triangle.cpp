#include "stdafx.h"
#include "P2C3_Triangle.h"
#include "AppTemplate.h"
//////////////////////////////////////////////////////////////////////////
int TriangleWnd::AppMain(HINSTANCE _hInstance)
{
	return AppTemplate_Main<TriangleWnd>(_hInstance, "Triangle");
}
//////////////////////////////////////////////////////////////////////////
TriangleWnd::TriangleWnd()
{
	m_pVertexBuf = NULL;
}

TriangleWnd::~TriangleWnd()
{

}


bool TriangleWnd::OnEnvCreate()
{
	m_pVertexBuf = Gfx_CreateVertexBuffer<SRVertex>(3);

	SRVertex* pVertex = NULL;
	m_pVertexBuf->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].SetXYZ(-1, 0, 2);
	pVertex[1].SetXYZ(0, 1, 2);
	pVertex[2].SetXYZ(1, 0, 2);

	pVertex[0] = SRVertex(-1, 0, 2);
	pVertex[1] = SRVertex(0, 1, 2);
	pVertex[2] = SRVertex(1, 0, 2);

	m_pVertexBuf->Unlock();

	Gfx_SetProjectionTransform();
	m_pD3Dev9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return true;
}

void TriangleWnd::OnEnvDestroy()
{
	SSAFE_RELEASE(m_pVertexBuf);
}

void TriangleWnd::OnDrawFrame()
{
	m_pD3Dev9->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	m_pD3Dev9->SetStreamSource(0, m_pVertexBuf, 0, sizeof(SRVertex));
	m_pD3Dev9->SetFVF(SRVertex::FVF);

	// Draw one triangle.
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}