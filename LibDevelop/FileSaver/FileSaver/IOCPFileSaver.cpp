#include "IOCPFileSaver.h"
#include <process.h>
#include <algorithm>
#include <iostream>

CIOCPFileSaver::CIOCPFileSaver()
{
	m_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	_beginthread(SaveWork, 0, this);
	hEvent = CreateEvent(NULL, FALSE, FALSE, L"");
}


CIOCPFileSaver::~CIOCPFileSaver()
{
	PostQueuedCompletionStatus(m_hIocp, 0, IOCP_STOP_KEY, NULL);
	WaitForSingleObject(hEvent, INFINITE);
}

HANDLE CIOCPFileSaver::CreateFile(std::string path)
{
	HANDLE hFile = CreateFileA(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return INVALID_HANDLE_VALUE;
	}
	HANDLE liocp = CreateIoCompletionPort(hFile, m_hIocp, 0, 0);
	if (liocp == NULL)
	{
		CloseHandle(hFile);
		return INVALID_HANDLE_VALUE;
	}

	std::cout << path << " file created!" << std::endl;

	m_hIocp = liocp;
	return hFile;
}

void CIOCPFileSaver::WriteAsync(char * lpBuf, size_t length, long long offsetInFile, bool needAutoDeleteBuffer, HANDLE hFile)
{
	LPOVERLAPPEDEx lpOv = new OVERLAPPEDEx;
	memset(lpOv, 0, sizeof(OVERLAPPEDEx));
	lpOv->m_hFile = hFile;
	lpOv->m_isNeedAutoDeleteBuffer = needAutoDeleteBuffer;
	lpOv->m_pData = lpBuf;
	memcpy(&lpOv->m_ov.Pointer, &offsetInFile, 8);
	WriteFile(hFile, lpBuf, length, NULL, (LPOVERLAPPED)lpOv);
}

void CIOCPFileSaver::CloseFile(HANDLE hFile)
{
	LPOVERLAPPEDEx lpOv = new OVERLAPPEDEx;
	memset(lpOv, 0, sizeof(OVERLAPPEDEx));
	lpOv->m_hFile = hFile;
	PostQueuedCompletionStatus(m_hIocp, 0, FILE_COLSE_KEY, (LPOVERLAPPED)lpOv);
}

void __cdecl CIOCPFileSaver::SaveWork(void *param)
{
	CIOCPFileSaver*pThis = (CIOCPFileSaver*)param;
	HANDLE iocp = pThis->m_hIocp;

	DWORD bytesTransferred = 0;
	ULONG_PTR key = 0;
	LPOVERLAPPEDEx lpov = NULL;

	while (key != IOCP_STOP_KEY)
	{
		GetQueuedCompletionStatus(iocp, &bytesTransferred, &key, (LPOVERLAPPED*)&lpov, INFINITE);
		switch (key)
		{
		case FILE_COLSE_KEY:
			CloseHandle(lpov->m_hFile);
			delete lpov;
			std::cout << bytesTransferred << " file closed!" << std::endl;
			break;
		case IOCP_STOP_KEY:
			std::cout << bytesTransferred << " IOCP stoped!" << std::endl;
			SetEvent(pThis->hEvent);
			break;
		default:
			if (lpov == NULL)
				break;
			if (lpov->m_isNeedAutoDeleteBuffer)
				delete[] lpov->m_pData;
			delete lpov;
			std::cout << bytesTransferred << " saved!" << std::endl;
			break;
		}
	}
	_endthread();
}
