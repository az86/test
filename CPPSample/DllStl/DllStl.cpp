#include <algorithm>
#include <iostream>

#define DLL_CLS __declspec(dllexport)
#include "DllStl.h"


CDllStl::CDllStl(void)
{
}


CDllStl::~CDllStl(void)
{
}

void CDllStl::Func(Vec & vec)
{
	std::for_each(vec.begin(), vec.end(), [&](int &val) { std::cout << val << std::endl; });
}

Vec& CDllStl::GetData()
{
	return m_data;
}
