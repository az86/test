// A short program to demonstrate dynamic memory allocation using 
// a structured exception handler. 

#include <windows.h>
#include <stdio.h>              // for printf
#include <stdlib.h>             // for exit

#define PAGELIMIT 80            // ask for this many pages

LPTSTR lpNxtPage;               // address of the next page to ask for
DWORD dwPages = 0;              // count of pages gotten so far
DWORD dwPageSize;               // the page size on this computer

INT PageFaultExceptionFilter(DWORD dwCode)
{
	LPVOID lpvResult;

	// If the exception is not a page fault, exit.

	if (dwCode != EXCEPTION_ACCESS_VIOLATION)
	{
		printf("Exception code = %d\n", dwCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	printf("Exception is a page fault\n");

	// If the reserved pages are used up, exit.

	if (dwPages >= PAGELIMIT)
	{
		printf("Exception: out of pages\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Otherwise, commit another page.

	lpvResult = VirtualAlloc(
		(LPVOID) lpNxtPage, // next page to commit
		dwPageSize,         // page size, in bytes
		MEM_COMMIT,         // allocate a committed page
		PAGE_READWRITE);    // read/write access
	if (lpvResult == NULL )
	{
		printf("VirtualAlloc failed\n");
		return EXCEPTION_EXECUTE_HANDLER;
	} else {
		printf ("Allocating another page.\n");
	}

	// Increment the page count, and advance lpNxtPage to the next page.

	dwPages++;
	lpNxtPage += dwPageSize;

	// Continue execution where the page fault occurred.

	return EXCEPTION_CONTINUE_EXECUTION;
}

VOID ErrorExit(LPTSTR lpMsg)
{
	printf ("Error! %s with error code of %ld\n",
		lpMsg, GetLastError ());
	exit (0);
}

VOID main(VOID)
{
	LPVOID lpvBase;               // base address of the test memory
	LPTSTR lpPtr;                 // generic character pointer
	BOOL bSuccess;                // flag
	DWORD i;                      // generic counter
	SYSTEM_INFO sSysInfo;         // useful information about the system

	GetSystemInfo(&sSysInfo);     // initialize the structure

	printf ("This computer has page size %d.\n", sSysInfo.dwPageSize);

	dwPageSize = sSysInfo.dwPageSize;

	// Reserve pages in the process's virtual address space.

	lpvBase = VirtualAlloc(
		NULL,                 // system selects address
		PAGELIMIT*dwPageSize, // size of allocation
		MEM_RESERVE,          // allocate reserved pages
		PAGE_NOACCESS);       // protection = no access
	if (lpvBase == NULL )
		ErrorExit("VirtualAlloc reserve failed");

	lpPtr = lpNxtPage = (LPTSTR) lpvBase;

	// Use structured exception handling when accessing the pages.
	// If a page fault occurs, the exception filter is executed to
	// commit another page from the reserved block of pages.

	for (i=0; i < PAGELIMIT*dwPageSize; i++)
	{
		__try
		{
			// Write to memory.

			lpPtr[i] = 'a';
		}

		// If there's a page fault, commit another page and try again.

		__except ( PageFaultExceptionFilter( GetExceptionCode() ) )
		{

			// This code is executed only if the filter function is 
			// unsuccessful in committing the next page.

			ExitProcess( GetLastError() );

		}

	}


	// Release the block of pages when you are finished using them.

	bSuccess = VirtualFree(
		lpvBase,       // base address of block
		0,             // bytes of committed pages
		MEM_RELEASE);  // decommit the pages

	printf ("Release %s.\n", bSuccess ? "succeeded" : "failed" );
}

