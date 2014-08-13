#include <core/RenderApp.h>
#include <core/RenderWnd.h>
#include <algorithm>
#include <Shlwapi.h>
//////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "shlwapi.lib")
//////////////////////////////////////////////////////////////////////////
SRRUNTIME_IMPLEMENT(SRRenderApp, SRObject, SRCLSNAME_SRRENDERAPP)

SRRenderApp::SRRenderApp()
{
	m_hInstance = 0;
	m_pRenderWnd = NULL;
	m_hIcon = NULL;
	m_uSettingFPS = 0;
	ZeroMemory(&m_stLastMsg, sizeof(MSG));
	m_fTimeDelta = 0.0f;
	m_bTerminate = false;
	m_nFPS = 0;
}

SRRenderApp::~SRRenderApp()
{
	DestroyMsgListener();
}


void SRRenderApp::AddMsgListener(SIMessageListener* _pListener)
{
	m_xMessageListenerList.push_back(_pListener);
}

void SRRenderApp::RemoveMsgListener(SIMessageListener* _pListener)
{
	std::remove(m_xMessageListenerList.begin(), m_xMessageListenerList.end(), _pListener);
}

void SRRenderApp::DestroyMsgListener()
{
	MessageListenerList::const_iterator begIter = m_xMessageListenerList.begin();
	MessageListenerList::const_iterator endIter = m_xMessageListenerList.end();

	for(begIter;
		begIter != endIter;
		++begIter)
	{
		SIMessageListener* pListener = *begIter;
		SSAFE_DELETE(pListener);
	}

	m_xMessageListenerList.clear();
}

bool SRRenderApp::QueryMessageListener(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	bool bSwallow = false;

	if(!m_xMessageListenerList.empty())
	{
		MessageListenerList::const_iterator begIter = m_xMessageListenerList.begin();
		MessageListenerList::const_iterator endIter = m_xMessageListenerList.end();

		for(begIter;
			begIter != endIter;
			++begIter)
		{
			SIMessageListener* pListener = *begIter;
			
			if(pListener->OnMessage(_hWnd, _uMsg, _wParam, _lParam))
			{
				bSwallow = true;
				break;
			}
		}
	}

	return bSwallow;
}

int SRRenderApp::MsgLoop()
{
	if(GetRenderWnd() == NULL)
	{
		return -1;
	}

	bool bGotMsg = false;
	MSG  msg;
	msg.message = WM_NULL;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

	UINT uFPS = GetSettingFPS();
	if(0 == uFPS)
	{
		uFPS = 30;
	}

	static const float s_fFPSGap = 1000.0f / (float)uFPS;
	static DWORD s_dwFPSGap = (DWORD)s_fFPSGap;
	static DWORD s_dwLastFrameTime = GetTickCount();

	while( WM_QUIT != msg.message  )
	{
		// Use PeekMessage() so we can use idle time to render the scene. 
		bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );

		if( bGotMsg )
		{
			// Translate and dispatch the message
			if(!QueryMessageListener(msg.hwnd, msg.message, msg.wParam, msg.lParam))
			{
				memcpy(&m_stLastMsg, &msg, sizeof(MSG));

				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			// Render a frame during idle time (no messages are waiting)
			DWORD dwCurrentTick = GetTickCount();

			DWORD dwTimeDelta = dwCurrentTick - s_dwLastFrameTime;
			m_fTimeDelta = (float)(dwCurrentTick - s_dwLastFrameTime) * 0.001f;
			
			GetRenderWnd()->OnDrawFrame();

			//	calculate fps
			static DWORD s_dwFpsCountTime = GetTickCount();
			static int s_nFpsCache = 0;

			++s_nFpsCache;
			if(GetTickCount() - s_dwFpsCountTime >= 1000)
			{
				m_nFPS = s_nFpsCache;
				s_nFpsCache = 0;
				s_dwFpsCountTime = GetTickCount();
			}
			//////////////////////////////////////////////////////////////////////////

			s_dwLastFrameTime = dwCurrentTick;

			DWORD dwCurrentTickAfterFrame = GetTickCount();
			DWORD dwTickDuringFrame = dwCurrentTickAfterFrame - dwCurrentTick;

			if(dwTickDuringFrame < s_dwFPSGap)
			{
				Sleep(s_dwFPSGap - dwTickDuringFrame);
			}
		}
	}

	return (int)msg.wParam;
}

void SRRenderApp::Terminate()
{
	SRRenderWnd* pRenderWnd = GetRenderWnd();
	if(pRenderWnd)
	{
		::DestroyWindow(pRenderWnd->GetHWND());
	}
}

const char* SRRenderApp::GetWorkingDir()
{
	static char s_szWorkingDir[MAX_PATH] = {0};

	if(0 == s_szWorkingDir[0])
	{
		GetModuleFileName(NULL, s_szWorkingDir, sizeof(s_szWorkingDir));
		PathRemoveFileSpec(s_szWorkingDir);
	}

	return s_szWorkingDir;
}