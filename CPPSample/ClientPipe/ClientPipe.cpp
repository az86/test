#include <windows.h> 
#include <iostream>
using namespace std;

#define BUFSIZE 64
LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\AzPipe"); 

int main(int argc, TCHAR *argv[]) 
{ 
	HANDLE hPipe = CreateFile(lpszPipename, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); 
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		cout << "create file failed  " << endl; 
		return -1;
	}
	
		

	//if (WaitNamedPipe(lpszPipename, 20000)) // All pipe instances are busy, so wait for 20 seconds. 
	//	cout << "WaitNamedPipe OK" << endl;

	// Send a message to the pipe server. 
	while (true)
	{
		char lpvMessage[BUFSIZE] ={0};
		static int i = 0;
		sprintf_s(lpvMessage, BUFSIZE, "Default message from client %x", i++);
		cout << lpvMessage << " is sent " << endl;
		DWORD cbWritten; 
		if (!WriteFile(hPipe, lpvMessage, strlen(lpvMessage), &cbWritten, NULL))
		{
			cout << "failed" << GetLastError() << endl;
		}
		Sleep(1000);
	}
	CloseHandle(hPipe); 
	return 0; 
}
