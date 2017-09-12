#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include "ConnectionException.h"
#include <iostream>
#include <process.h>
using namespace std;

void InitWinSock()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
		cout << "Error at WSAStartup()" << endl;
}

unsigned __stdcall DoWork(LPVOID param)
{
	HANDLE hIocp = (HANDLE) param;
	WSABUF wsaBuf;
	wsaBuf.buf = new char[128];
	wsaBuf.len= 128;
	DWORD byteRecv=0;
	DWORD flag=MSG_PARTIAL;
	OVERLAPPED ol = {0};
	ZeroMemory(wsaBuf.buf, wsaBuf.len);

	DWORD numberOfBytes = 0;
	LPOVERLAPPED p;
	ULONG_PTR cpKey;

	while (GetQueuedCompletionStatus(hIocp, &numberOfBytes, &cpKey, &p, INFINITE))
	{
		auto sock = (SOCKET) cpKey; 
		sockaddr_in sockAddr;
		int len = sizeof(sockAddr);
		getpeername(sock, (sockaddr*)&sockAddr, &len);
		if (numberOfBytes == 0)
		{
			cout << "client " << inet_ntoa(sockAddr.sin_addr) << ": " << ntohs(sockAddr.sin_port) << " quit!" << endl;
			closesocket(sock);
		}
		else
		{
			cout << "client " << inet_ntoa(sockAddr.sin_addr) << ": " << ntohs(sockAddr.sin_port) << "\n\t"<< wsaBuf.buf << endl;
			ZeroMemory(wsaBuf.buf, wsaBuf.len);
			WSARecv(sock, &wsaBuf, 1, &byteRecv, &flag, &ol, NULL);
		}
	}
	return 0;
}

int main()
{
	try
	{
		InitWinSock();
		SOCKET srvSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (srvSock ==  INVALID_SOCKET)
			throw CConnectionException("create socket failed!");
		sockaddr_in service;
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = inet_addr("127.0.0.1");
		service.sin_port = htons(7777);
		
		if (SOCKET_ERROR == bind(srvSock, (sockaddr*)&service, sizeof(service)))
			throw CConnectionException("bind failed!");
		
		listen(srvSock, SOMAXCONN);


		HANDLE hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if (hIocp == INVALID_HANDLE_VALUE)
			cout << "create iocp failed " << endl;
		
		_beginthreadex(nullptr, 0, DoWork, hIocp, 0, nullptr);
		_beginthreadex(nullptr, 0, DoWork, hIocp, 0, nullptr);
		_beginthreadex(nullptr, 0, DoWork, hIocp, 0, nullptr);

		while (true)
		{
			sockaddr_in client = {0};
			int val = sizeof(client);
			SOCKET clientSock = WSAAccept(srvSock, (sockaddr*)&client, &val, NULL, NULL);
			if (NULL == clientSock)
				throw CConnectionException("WSAAccept failed!");
			else
				cout << "client " << inet_ntoa(client.sin_addr) << ": " << ntohs(client.sin_port) << " connect" << endl;
			
			if (NULL == CreateIoCompletionPort((HANDLE)clientSock, hIocp, clientSock, 0))
				cout << "create iocp failed " << endl;
			PostQueuedCompletionStatus(hIocp, 1, clientSock, NULL);
		}
		CloseHandle(hIocp);
	}
	catch (CConnectionException & e)
	{
		cerr << e.what() << "error number:" << e.m_errorNo << endl;
	}
}

