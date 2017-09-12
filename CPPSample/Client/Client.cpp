#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
using namespace std;

void InitWinSock()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
		cout << "Error at WSAStartup()" << endl;
}

int main()
{
	InitWinSock();
	SOCKET clientSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	sockaddr_in clientService; 
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	clientService.sin_port = htons(7777);


	if ( connect(clientSock, (sockaddr*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		cout <<  "Failed to connect" << WSAGetLastError()<< endl;
		WSACleanup();
		return 1;
	}

	int n = 30;
	while (n--)
	{
		Sleep(100);
		char buf[64] = {0};
		_itoa_s(n, buf, 64, 10);
		send(clientSock, buf, strlen(buf)+1, 0);
		cout << "OK "<< endl;
	}
	closesocket(clientSock);
	return 0;
}