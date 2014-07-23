#ifndef _INC_SROBJECT_
#define _INC_SROBJECT_
//////////////////////////////////////////////////////////////////////////
#include <string.h>
#include "SrenderDef.h"
//////////////////////////////////////////////////////////////////////////
#define SRRUNTIME_IMPLEMENT(CLSTYPE, BASECLSTYPE, CLSNAME)	bool CLSTYPE::IsClass(const char* _pszClsName)\
															{\
																if(0 == strcmp(_pszClsName, CLSNAME)){return true;}\
																else {return BASECLSTYPE::IsClass(_pszClsName);}\
															}
#define SRRUNTIME_DECLARE()									public:virtual bool IsClass(const char* _pszClsName);

//////////////////////////////////////////////////////////////////////////
//	runtime information support
class SRObject
{
public:
	virtual bool IsClass(const char* _pszClsName)
	{
		if(0 == strcmp(_pszClsName, SRCLSNAME_SROBJECT))
		{
			return true;
		}

		return false;
	}
};
//////////////////////////////////////////////////////////////////////////
#endif