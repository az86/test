#pragma once
#include <iostream>

struct CDump
{
	template<typename T>
	CDump & operator << (const T & val)
	{
		os << val;
		return *this;
	}
	CDump(std::ostream &os) : os(os){}
private:
	std::ostream &os;
};

extern CDump dump;