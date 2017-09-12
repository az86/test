#include <windows.h>
#include <stdio.h>

char *we;

int ExceFilter(int ExceCode)
{
	//	delete gPm;
	we[3] = 0;
	printf("Alloc new mem\n");
	return EXCEPTION_CONTINUE_EXECUTION;
}

void Func(char *p)
{
	if (p[3] != 0)
	{
		throw 1;
	}
}
int main()
{
	we = new char[4];
	we[0] = 's';
	we[1] = 's';
	we[2] = 's';
	we[3] = 's';
	__try
	{
		Func(we);
		printf("{%d}\n");
	}
	__except(ExceFilter(GetExceptionCode()))
	{
		//gPm = we;
	}
	return 0;
}