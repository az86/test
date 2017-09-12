#pragma once
#include "CommonDefs.h"

enum A
{
	All7,
	All9
};

class DLL_CLASS CTest
{
public:
	CTest(void);
	~CTest(void);
	void GetArray(int *p, int bufLen, A a);
};

