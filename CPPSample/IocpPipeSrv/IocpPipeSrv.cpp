#include <windows.h>
#include <iostream>
#include <process.h>
using namespace std;

unsigned __stdcall DoWork(LPVOID param);
int main()
{
	LPCTSTR pipeName = TEXT("\\\\.\\pipe\\AzPipe");
	try
	{
		HANDLE hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_ACCEPT_REMOTE_CLIENTS, PIPE_UNLIMITED_INSTANCES, 64, 64, 0, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			cout << GetLastError() << endl;
			throw exception("CreateNamedPipe failed");
		}
// 		_beginthreadex(nullptr, 0, DoWork, hIocp, 0, nullptr);
// 		_beginthreadex(nullptr, 0, DoWork, hIocp, 0, nullptr);
// 		_beginthreadex(nullptr, 0, DoWork, hIocp, 0, nullptr);

		OVERLAPPED olp = {0};
		olp.Offset = 64;
		ConnectNamedPipe(hPipe, &olp); 

		HANDLE hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if (hIocp == INVALID_HANDLE_VALUE)
		{
			cout << GetLastError() << endl;
			cout << "create iocp failed " << endl;
		}
		if (NULL == CreateIoCompletionPort((HANDLE)hPipe, hIocp, 333, 0))
		{
			cout << GetLastError() << endl;
			cout << "create iocp failed " << endl;
		}

		OVERLAPPED olpRead = {0};
		char buf[64] = {0};
		DWORD numberOfBytes = 0;
		LPOVERLAPPED p;
		ULONG_PTR cpKey;

		while (GetQueuedCompletionStatus(hIocp, &numberOfBytes, &cpKey, &p, INFINITE))
		{
			if (cpKey == 333 && p==&olpRead)
			{
				static int i = 0;
				cout << "READ " << i++  << " -- " << numberOfBytes << " transfered : " <<  buf << endl;
				numberOfBytes = 0;
				ReadFile(hPipe, buf, 64, NULL, &olpRead);
			}
			if (cpKey == 333 && p==&olp)
			{
				cout << "connected " << endl;
				ReadFile(hPipe, buf, 64, NULL, &olpRead);
			}

		}
	}
	catch (exception & e)
	{
		cerr << e.what() << endl;
	}
}
