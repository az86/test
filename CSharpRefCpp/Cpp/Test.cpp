#include <algorithm>
#include <iterator>
#define DLL_CLASS __declspec(dllexport)
#include "Test.h"

CTest::CTest(void)
{
}


CTest::~CTest(void)
{
}

void CTest::GetArray(int *p, int bufLen, A a)
{
	switch (a)
	{
	case All7:
		std::fill(p, p + bufLen, 7);
		break;	
	case All9:
		std::fill(p, p + bufLen, 9);
		break;
	default:
		std::fill(p, p + bufLen, 0);
		break;
	}
}
