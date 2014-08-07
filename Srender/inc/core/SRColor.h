#ifndef _INC_SRCOLOR_
#define _INC_SRCOLOR_
//////////////////////////////////////////////////////////////////////////
#include <d3dx9.h>
//////////////////////////////////////////////////////////////////////////
class SRColor
{
public:
	enum CommonColor
	{
		CC_WHITE,
		CC_BLACK,
		CC_RED,
		CC_GREEN,
		CC_BLUE,
		CC_YELLOW,
		CC_CYAN,
		CC_MAGENTA,
	};

public:
	static D3DXCOLOR GetCommonColor(CommonColor _eColor)
	{
		switch(_eColor)
		{
		case CC_WHITE:
			{
				return D3DXCOLOR(D3DCOLOR_XRGB(255, 255, 255));
			}break;
		case CC_BLACK:
			{
				return D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 0));
			}break;
		case CC_RED:
			{
				return D3DXCOLOR(D3DCOLOR_XRGB(255, 0, 0));
			}break;
		case CC_GREEN:
			{
				return D3DXCOLOR(D3DCOLOR_XRGB(0, 255, 0));
			}break;
		case CC_BLUE:
			{
				return D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 255));
			}break;
		case CC_YELLOW:
			{
				return D3DXCOLOR(D3DCOLOR_XRGB(255, 255, 0));
			}break;
		case CC_CYAN:
			{
				return D3DXCOLOR(D3DCOLOR_XRGB(0, 255, 255));
			}break;
		case CC_MAGENTA:
			{
				return D3DXCOLOR(D3DCOLOR_XRGB(255, 0, 255));
			}break;
		}

		return D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 0));
	}
};
//////////////////////////////////////////////////////////////////////////
#endif