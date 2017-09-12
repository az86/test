#pragma once
#include <vector>
#include <Windows.h>

typedef double * Iterator;
typedef void (*pFun)(Iterator it);

class CParallel
{
public:
	void AddParallelTask(Iterator pBegin, Iterator pEnd, pFun pfun);
	void Initialize(int cpuCount, long maxTaskCount);
	void Release();
	static CParallel & GetInstance();
	~CParallel(void);
private:
	CParallel();
	static unsigned __stdcall WorkFunc(void *para);

	static CParallel * m_pThis;
	std::vector<uintptr_t> m_hThreads;
	static HANDLE m_hSemphore;
	static HANDLE m_hEvent;
	static bool m_beRun;
	static pFun m_fun;
	static Iterator m_pbegin;
	static Iterator m_pend;
};

