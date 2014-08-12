#ifndef _INC_SRVERTEX_
#define _INC_SRVERTEX_
//////////////////////////////////////////////////////////////////////////
#include <d3dx9.h>
//////////////////////////////////////////////////////////////////////////
struct SRVertex
{
	SRVertex()
	{
		m_fVertexX = m_fVertexY = m_fVertexZ = 0.0f;
		//m_dwColor = 0;
	}
	SRVertex(float _x, float _y, float _z)
	{
		SetX(_x);
		SetY(_y);
		SetZ(_z);
	}
	/*SRVertex(float _x, float _y, float _z, DWORD _dwColor)
	{
		SetX(_x);
		SetY(_y);
		SetZ(_z);
		m_dwColor = _dwColor;
	}*/

	float GetX()
	{
		return m_fVertexX;
	}
	float GetY()
	{
		return m_fVertexY;
	}
	float GetZ()
	{
		return m_fVertexZ;
	}

	void SetXYZ(float _x, float _y, float _z)
	{
		SetX(_x);
		SetY(_y);
		SetZ(_z);
	}
	void SetX(float _x)
	{
		m_fVertexX = _x;
	}
	void SetY(float _y)
	{
		m_fVertexY = _y;
	}
	void SetZ(float _z)
	{
		m_fVertexZ = _z;
	}

	//////////////////////////////////////////////////////////////////////////
	//	coordinate
	float m_fVertexX, m_fVertexY, m_fVertexZ;
	//	color
	//D3DCOLOR m_dwColor;
	//////////////////////////////////////////////////////////////////////////
	//	flexible vertex
	static const DWORD FVF;
};

//////////////////////////////////////////////////////////////////////////
struct SRColorVertex : public SRVertex
{
	SRColorVertex()
	{
		m_dwColor = 0;
	}
	SRColorVertex(float _x, float _y, float _z, D3DCOLOR _dwColor) : SRVertex(_x, _y, _z)
	{
		m_dwColor = _dwColor;
	}

	//////////////////////////////////////////////////////////////////////////
	//	color
	D3DCOLOR m_dwColor;
	//////////////////////////////////////////////////////////////////////////
	//	fvf
	static const DWORD FVF;
};

//////////////////////////////////////////////////////////////////////////
struct SRNormalVertex : public SRVertex
{
	SRNormalVertex()
	{
		m_fNormalX = m_fNormalY = m_fNormalZ = 0.0f;
	}
	SRNormalVertex(float _x, float _y, float _z)
	{
		SetXYZ(_x, _y, _z);
	}
	SRNormalVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz)
	{
		SetXYZ(_x, _y, _z);

		m_fNormalX = _nx;
		m_fNormalY = _ny;
		m_fNormalZ = _nz;
	}

	void SetNormalXYZ(float _nx, float _ny, float _nz)
	{
		m_fNormalX = _nx;
		m_fNormalY = _ny;
		m_fNormalZ = _nz;
	}
	//////////////////////////////////////////////////////////////////////////
	//	vertex normal
	float m_fNormalX, m_fNormalY, m_fNormalZ;
	//////////////////////////////////////////////////////////////////////////
	//	fvf
	static const DWORD FVF;
};

//////////////////////////////////////////////////////////////////////////
struct SRNormalTextureVertex : public SRNormalVertex
{
	SRNormalTextureVertex()
	{
		m_fTextureX = m_fTextureY = 0.0f;
	}

	SRNormalTextureVertex(float _x, float _y, float _z)
	{
		SetXYZ(_x, _y, _z);

		m_fTextureX = m_fTextureY = 0.0f;
	}

	SRNormalTextureVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz) : SRNormalVertex(_x, _y, _z, _nx, _ny, _nz)
	{
		m_fTextureX = m_fTextureY = 0.0f;
	}

	void SetTextureXY(float _tx, float _ty)
	{
		m_fTextureX = _tx;
		m_fTextureY = _ty;
	}

	SRNormalTextureVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _tx, float _ty) : SRNormalVertex(_x, _y, _z, _nx, _ny, _nz)
	{
		m_fTextureX = _tx;
		m_fTextureY = _ty;
	}

	//////////////////////////////////////////////////////////////////////////
	//	texture coordinates
	float m_fTextureX, m_fTextureY;
	//////////////////////////////////////////////////////////////////////////
	//	fvf
	static const DWORD FVF;
};
//////////////////////////////////////////////////////////////////////////
#endif