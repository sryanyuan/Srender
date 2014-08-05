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
	}
	SRVertex(float _x, float _y, float _z)
	{
		SetX(_x);
		SetY(_y);
		SetZ(_z);
	}

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
		SetZ(_x);
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
	float m_fVertexX, m_fVertexY, m_fVertexZ;
	//////////////////////////////////////////////////////////////////////////
	static const DWORD FVF;
};
//////////////////////////////////////////////////////////////////////////
#endif