#ifndef _INC_SRENDERDEF_
#define _INC_SRENDERDEF_
//////////////////////////////////////////////////////////////////////////
#include "SRCLSNameDef.h"
//////////////////////////////////////////////////////////////////////////

#ifdef _SRENDER_EXPORT_
	#define SRENDER_API	
#else
	#define SRENDER_API
#endif

#define SSAFE_DELETE(p)				do{if(p){delete p;p=NULL;}}while(0);
#define SSAFE_DELETE_ARRAPY(p)		do{if(p){delete[]p;p=NULL;}}while(0);

#define MUTABLE_PROPERTY_BASETYPE(type,var,name)		protected:type var;\
														public:type Get##name(){return var;}\
														public:void Set##name(type _var){var = _var;}

#define READONLY_PROPERTY_BASETYPE(type,var,name)		protected:type var;\
														public:const type Get##name(){return var;}

#define SINGLETON_DECLARE(CLSNAME)						public:static CLSNAME* GetInstancePtr(){static CLSNAME s_ins;return &s_ins;};

#define MSGBOX_ERR(text)								::MessageBox(NULL, text, "ERROR", MB_ICONERROR | MB_OK)

#define WNDCLS_SRENDER									"SRRenderWnd"

//////////////////////////////////////////////////////////////////////////
#endif