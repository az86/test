#include "Parallel.h"
#include <process.h>
#include <tchar.h>

CParallel* CParallel::m_pThis = nullptr;
HANDLE CParallel::m_hSemphore = NULL;
HANDLE CParallel::m_hEvent = NULL;
pFun CParallel::m_fun;
Iterator CParallel::m_pbegin;
Iterator CParallel::m_pend;
bool CParallel::m_beRun = false;

CParallel::CParallel(void)
{
}

CParallel::~CParallel(void)
{

}

void CParallel::Initialize(int cpuCount, long maxTaskCount)
{
	m_beRun = true;
	m_hSemphore = CreateSemaphore(NULL, 0, maxTaskCount, _T(""));
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, _T(""));
	for (auto i = 0; i != cpuCount; ++i)
	{
		auto th = _beginthreadex(nullptr, 0, WorkFunc, this, 0, nullptr);
		m_hThreads.push_back(th);
	}
}

CParallel & CParallel::GetInstance()
{
	if (m_pThis == nullptr)
		m_pThis = new CParallel();
	return *m_pThis;
}

unsigned __stdcall CParallel::WorkFunc(void * para)
{
	while (m_beRun)
	{
		WaitForSingleObject(m_hSemphore, INFINITE);
		Iterator pCurrrent = (Iterator)InterlockedExchangeAdd((long*)&m_pbegin, sizeof(*m_pbegin));
		if (pCurrrent == m_pend)
		{
			SetEvent(m_hEvent);
		}
		else
		{
			m_fun(pCurrrent);
		}
	}
	_endthread();
	return 0;
}

void CParallel::AddParallelTask(Iterator pBegin, Iterator pEnd, pFun pfun )
{
	m_pbegin = pBegin;
	m_pend = pEnd;
	m_fun = pfun;
	ReleaseSemaphore(m_hSemphore, pEnd - pBegin + 1, NULL);
	WaitForSingleObject(m_hEvent, INFINITE);
	m_pbegin--;
}

void CParallel::Release()
{
	m_beRun = false;
	for (auto it = m_hThreads.begin(); it != m_hThreads.end(); ++it)
	{
		TerminateThread((HANDLE)*it, 0);
		CloseHandle((HANDLE)*it);
	}
	CloseHandle(m_hEvent);
	CloseHandle(m_hSemphore);
	delete m_pThis;
}
