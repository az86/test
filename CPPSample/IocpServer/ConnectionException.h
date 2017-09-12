#pragma once
#include <exception>
class CConnectionException : public std::exception
{
public:
	CConnectionException(void);
	CConnectionException(const char *info);
	~CConnectionException(void);
	int m_errorNo;
};

