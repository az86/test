#include <omp.h>
#include <iostream>
#include <algorithm>
using namespace std;
#include "Parallel.h"

void Fun(double *p)
{
	(*p)+=10;
}

int main()
{
 	double k[8] = {0};
 	CParallel& parallel = CParallel::GetInstance();
 	parallel.Initialize(4, 1000);
 	parallel.AddParallelTask(k, k+8, Fun);
 	for_each(k, k+8, [](double &val){cout<< val<<endl;});
 	parallel.Release();


	cout << "\\\\\\\\\\\\\\\\\\\\\\OpenMP\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
	
	int threadCount = 0;
	int testVal = 0;
#pragma omp parallel		// need to compile with omp
	{
#pragma omp for
		for (int i = 0; i < 10; ++i)			//core4 cpu����ű��ֳ�0-4,5-9,10-14,15-29��4����������
		{	
			testVal = i;
			cout << "testVal[" << omp_get_thread_num() << "] = " << testVal << endl;
			Sleep(100 * i % 2);
		}
#pragma omp barrier //�ȴ�����4�����Ķ�������������

		cout << "tid = " << omp_get_thread_num() << endl;
		threadCount++;
		Sleep(100);
	}
	return 0;
}
