#include <windows.h>
#include <iostream>
#include <tchar.h>
using namespace std;

VOID CALLBACK WaitCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WAIT Wait, TP_WAIT_RESULT WaitResult)
{
	cout << "ok"<< endl;
}

void TestWaitPool()
{
	HANDLE hEvt = CreateEvent(NULL, FALSE, FALSE, _T(""));
	TP_CALLBACK_ENVIRON  env;
	InitializeThreadpoolEnvironment(&env);
	PTP_WAIT poolWait = CreateThreadpoolWait(WaitCallback, NULL, &env);
	SetThreadpoolWait(poolWait, hEvt, NULL);
	WaitForThreadpoolWaitCallbacks(poolWait, FALSE);
	Sleep(3000);
	SetEvent(hEvt);
	Sleep(3000);
}

VOID CALLBACK TimerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WAIT Wait, PTP_TIMER Timer)
{
	cout << "ok"<< endl;
}

VOID CALLBACK MyTimerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Parameter, PTP_TIMER Timer)
{
	//
	// Do something when the timer fires
	//
	cout << "sdfsdfsdf " << endl;
}

VOID DemoCleanupPersistentWorkTimer()
{
	BOOL bRet = FALSE;
	PTP_WORK work = NULL;
	PTP_TIMER timer = NULL;
	PTP_POOL pool = NULL;
	TP_CALLBACK_ENVIRON CallBackEnviron;
	PTP_CLEANUP_GROUP cleanupgroup = NULL;
	FILETIME FileDueTime;
	ULARGE_INTEGER ulDueTime;
	UINT rollback = 0;

	InitializeThreadpoolEnvironment(&CallBackEnviron);

	timer = CreateThreadpoolTimer(
		(PTP_TIMER_CALLBACK) MyTimerCallback,
		NULL, &CallBackEnviron);


	rollback = 4;  // Timer creation succeeded

	//
	// Set the timer to fire in one second
	//
	ulDueTime.QuadPart = (LONGLONG) -(1 * 10 * 1000 * 1000);
	FileDueTime.dwHighDateTime = ulDueTime.HighPart;
	FileDueTime.dwLowDateTime  = ulDueTime.LowPart;

	SetThreadpoolTimer(timer,
		&FileDueTime,
		500,
		0);

	Sleep(1500000);
}


int main()
{
	DemoCleanupPersistentWorkTimer();
	return 0;
}