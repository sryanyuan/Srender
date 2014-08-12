#include <core/SRVertex.h>
//////////////////////////////////////////////////////////////////////////
const DWORD SRVertex::FVF = D3DFVF_XYZ;

const DWORD SRColorVertex::FVF = SRVertex::FVF | D3DFVF_DIFFUSE;

const DWORD SRNormalVertex::FVF = SRVertex::FVF | D3DFVF_NORMAL;

const DWORD SRNormalTextureVertex::FVF = SRNormalVertex::FVF | D3DFVF_TEX1;