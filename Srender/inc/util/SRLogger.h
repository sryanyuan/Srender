#ifndef _INC_SRLOGGER_
#define _INC_SRLOGGER_
//////////////////////////////////////////////////////////////////////////
#define GOOGLE_GLOG_DLL_DECL
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "./glog/glog/logging.h"
#include "../core/SrenderDef.h"
#include <string>
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	#pragma comment(lib, "libglog_static_d.lib")
#else
	#pragma comment(lib, "libglog_static.lib")
#endif
//////////////////////////////////////////////////////////////////////////
#define SRLOG_INFO			LOG(INFO)
#define SRLOG_WARNING		LOG(WARNING)
#define SRLOG_ERROR			LOG(ERROR)
#define SRLOG_FATAL			LOG(FATAL)
//////////////////////////////////////////////////////////////////////////
class SRENDER_API SRLogger
{
	SINGLETON_DECLARE(SRLogger)

public:
	~SRLogger();
protected:
	SRLogger();

public:
	bool Initialize(const char* _pszLogFile);
	void UnInitialize();

protected:
	std::string m_xLogFile;
	bool m_bInitialized;
};
//////////////////////////////////////////////////////////////////////////
#endif