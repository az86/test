#include "ConnectionException.h"
#include "Winsock2.h"
#pragma comment(lib, "Ws2_32.lib")

CConnectionException::CConnectionException(void)
{
	m_errorNo = WSAGetLastError();
}

CConnectionException::CConnectionException(const char *info) : exception(info)
{
	m_errorNo = WSAGetLastError();
}


CConnectionException::~CConnectionException(void)
{
}
