#pragma once
#include <windows.h>
#include <string>

class CIOCPFileSaver
{
public:

	typedef struct OVERLAPPEDEx
	{
		OVERLAPPED m_ov;
		HANDLE m_hFile;
		char *m_pData;
		bool m_isNeedAutoDeleteBuffer;
	} *LPOVERLAPPEDEx;

	CIOCPFileSaver();
	~CIOCPFileSaver();
	
	//////////////////////////////////////////////////////////////////////////
	// Function: CreateFile
	// param path: File path you want created.
	// return: File HANDLE, When you want save data in multiply files, you can use this parameter in WriteFile function.
	//				If the function succeeds, the return value is an open handle to the specified file.
	//				If the function fails, the return value is INVALID_HANDLE_VALUE.To get extended error information, call GetLastError.
	//////////////////////////////////////////////////////////////////////////
	HANDLE CreateFile(std::string path);

	//////////////////////////////////////////////////////////////////////////
	// Function: WriteAsync
	// param lpBuf: Buffer contains data you want to save.
	// param length: byte count in lpBuf.
	// param needAutoDeleteBuffer: The parameter set true, if you need the function call delete[] operator auto automatically.
	// param hFile: File Handle returned by CreateFile.
	//////////////////////////////////////////////////////////////////////////
	void WriteAsync(char * lpBuf, size_t length, long long offsetInFile, bool needAutoDeleteBuffer, HANDLE hFile);

	//////////////////////////////////////////////////////////////////////////
	// Function: CloseFile
	// param hFile: File Handle returned by CreateFile.
	//////////////////////////////////////////////////////////////////////////
	void CloseFile(HANDLE hFile);

private:

	static const uintptr_t FILE_COLSE_KEY = 0xFFFF;
	static const uintptr_t IOCP_STOP_KEY = 0xFFFFFFFF;
	static const int MAX_FILE_COUNT = 0x100;

	HANDLE m_hIocp;
	HANDLE hEvent;

	static void __cdecl SaveWork(void *param);
};

