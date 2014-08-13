#include <util/SRLogger.h>
#include <direct.h>
//////////////////////////////////////////////////////////////////////////
SRLogger::SRLogger()
{
	m_bInitialized = false;
}

SRLogger::~SRLogger()
{

}


bool SRLogger::Initialize(const char* _pszLogFile)
{
	if(NULL == _pszLogFile)
	{
		return false;
	}
	if(strlen(_pszLogFile) == 0)
	{
		return false;
	}

	char szLogPath[MAX_PATH] = {0};
	strcpy(szLogPath, _pszLogFile);

	if(!PathFileExists(szLogPath))
	{
		if(0 != mkdir(szLogPath))
		{
			return false;
		}
	}

	char szModuleFileName[MAX_PATH] = {0};
	GetModuleFileName(NULL, szModuleFileName, sizeof(szModuleFileName));
	google::InitGoogleLogging(szModuleFileName);
	google::SetLogDestination(google::GLOG_INFO, _pszLogFile);

	m_xLogFile = _pszLogFile;

	return true;
}

void SRLogger::UnInitialize()
{
	google::ShutdownGoogleLogging();
}