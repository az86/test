#pragma once
#include <exception>

class NormalException : public std::exception
{
public:
	NormalException(const char * msg) : exception (msg)
	{
	}
};