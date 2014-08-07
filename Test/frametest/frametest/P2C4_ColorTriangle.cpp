#include "stdafx.h"
#include "P2C4_ColorTriangle.h"
#include <core/SRColor.h>
//////////////////////////////////////////////////////////////////////////
ColorTriangleWnd::ColorTriangleWnd()
{
	m_pVertexBuf = NULL;
	m_pFont = NULL;
}

ColorTriangleWnd::~ColorTriangleWnd()
{

}


bool ColorTriangleWnd::OnEnvCreate()
{
	m_pVertexBuf = Gfx_CreateVertexBuffer<SRColorVertex>(3);

	if(NULL == m_pVertexBuf)
	{
		return false;
	}

	SRColorVertex* pVertex = NULL;
	m_pVertexBuf->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = SRColorVertex(-1.0f, 0.0f, 2.0f, SRColor::GetCommonColor(SRColor::CC_RED));
	pVertex[1] = SRColorVertex(0.0f, 1.0f, 2.0f, SRColor::GetCommonColor(SRColor::CC_GREEN));
	pVertex[2] = SRColorVertex(1.0f, 0.0f, 2.0f, SRColor::GetCommonColor(SRColor::CC_BLUE));

	m_pVertexBuf->Unlock();

	HRESULT hr = D3DXCreateFont(m_pD3Dev9, 30, 0, 0, 1, FALSE, DEFAULT_CHARSET,   
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("ËÎÌו"), &m_pFont);
	if(D3D_OK != hr)
	{
		return false;
	}

	Gfx_SetProjectionTransform();
	m_pD3Dev9->SetRenderState(D3DRS_LIGHTING, FALSE);

	return true;
}

void ColorTriangleWnd::OnEnvDestroy()
{
	SSAFE_RELEASE(m_pVertexBuf);
	SSAFE_RELEASE(m_pFont);
}

void ColorTriangleWnd::OnDrawFrame()
{
	SRRenderApp* pApp = SRRenderApp::GetInstancePtr();

	m_pD3Dev9->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	m_pD3Dev9->BeginScene();

	m_pD3Dev9->SetStreamSource(0, m_pVertexBuf, 0, sizeof(SRColorVertex));
	m_pD3Dev9->SetFVF(SRColorVertex::FVF);

	//	flat shade mode
	D3DXMATRIX mx;
	D3DXMatrixTranslation(&mx, -1.1f, 0.0f, 0.0f);
	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mx);
	m_pD3Dev9->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	//	gouraud shade mode
	D3DXMatrixTranslation(&mx, 1.1f, 0.0f, 0.0f);
	m_pD3Dev9->SetTransform(D3DTS_WORLD, &mx);
	m_pD3Dev9->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	m_pD3Dev9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	//	draw fps
	char szMsgBuf[256] = {0};
	sprintf(szMsgBuf, "FPS [%d]", pApp->GetFPS());
	RECT rcDrawPos;
	rcDrawPos.top = 10;
	rcDrawPos.bottom = rcDrawPos.top + 30;
	rcDrawPos.left = 0;
	rcDrawPos.right = GetWindowWidth();
	m_pFont->DrawTextA(0, szMsgBuf, -1, &rcDrawPos, DT_CENTER, D3DCOLOR_XRGB(68, 139, 255));

	m_pD3Dev9->EndScene();
	m_pD3Dev9->Present(0, 0, 0, 0);
}