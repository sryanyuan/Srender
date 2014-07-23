#include <util/debug.h>
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