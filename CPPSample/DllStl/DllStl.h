#pragma once

#include <vector>
#ifndef DLL_CLS
#define DLL_CLS __declspec(dllimport)
#endif

#define COMPILE_VER	1600		//vs2010sp1 version
#define NO_WARNING	_MSC_VER == COMPILE_VER
#if (NO_WARNING)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

typedef std::vector<int> Vec;

class DLL_CLS CDllStl
{
public:
	CDllStl(void);
	~CDllStl(void);
	void Func(Vec &vec);
	Vec&GetData();
private:
	Vec m_data;
};

#if (NO_WARNING)
#pragma warning(pop)
#endif