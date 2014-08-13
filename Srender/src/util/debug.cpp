#include <util/debug.h>
#include <stdarg.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
LPSTR FormatErrorCode(DWORD _dwErrorCode)
{  
	HLOCAL LocalAddress=NULL;  
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,  
		NULL,_dwErrorCode,0,(PTSTR)&LocalAddress,0,NULL);  
	return (LPSTR)LocalAddress;  
}

void ShowErrorCodeMsgBox(DWORD _dwErrorCode)
{
	LPSTR pszErrorMsg = FormatErrorCode(_dwErrorCode);

	if(pszErrorMsg)
	{
		MSGBOX_ERR(pszErrorMsg);
	}
	//SSAFE_DELETE_ARRAPY(pszErrorMsg);
}

void SRTrace(const char* _pszFormat, ...)
{
#ifdef _DEBUG
	char szMsg[4096] = {0};

	va_list ap;

	va_start(ap, _pszFormat);
	vsprintf(szMsg, _pszFormat, ap);
	va_end(ap);

	strcat(szMsg, "\n");
	printf(szMsg);
#endif
}