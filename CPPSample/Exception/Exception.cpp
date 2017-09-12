#include <iostream>
#include <ctime>
#include "ExceptionCls.h"
using namespace std;
#include <Windows.h>

void ForTry();
void TryFor();
void CoreEx(int);
#define TestTime  1000000

int main()
{
	ForTry();
	TryFor();
	TryFor();
	ForTry();
}

void ForTry()
{
	auto ts = clock();
	for (auto i = 0; i != TestTime; i++)
	{
		try
		{
			CoreEx(i);
		}
		catch (NormalException &)
		{
			//cout << e.what() << endl;
		}
	}
	auto te = clock();
	cout << "ForTry:" << te - ts << endl;
}


void TryFor()
{
	auto i = 0;
	auto ts = clock();
	while (i != TestTime)
	{
		try
		{
			for (; i != TestTime; i++)
			{
				CoreEx(i);
			}
		}
		catch (NormalException &)
		{
			//cout << e.what() << endl;
			i++;
		}
	}
	auto te = clock();
	cout << "TryFor:" << te - ts << endl;

}

void CoreEx(int para)
{
	if (!(para & 0x3FF))
	{
		throw NormalException("normal exception raised!");
	}
}