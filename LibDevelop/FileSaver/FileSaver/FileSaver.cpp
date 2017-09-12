#include <stdio.h>
#include <process.h>
#include "IOCPFileSaver.h"

int main()
{
	CIOCPFileSaver iocpFileSaver;
	int fileIndex = 0;
	
	int i = 0;
	char buf[] = { 0, 1, 2, 3 };
	char path[256];

	HANDLE hFile = NULL;

	for (char ch = getchar(); ch != 'q'; ch = getchar())
	{
		switch (ch)
		{
		case 'r':
			iocpFileSaver.CloseFile(hFile);
			break;

		case 'c':
			sprintf_s(path, 256, "abc.%d.dat",  fileIndex++);
			hFile = iocpFileSaver.CreateFile(path);
		case '\n':
			break;
		default:
			iocpFileSaver.WriteAsync(buf, 4, i, false, hFile);
			i += 4;
			break;
		}
	}
	Sleep(1000);
	return 0;
}
