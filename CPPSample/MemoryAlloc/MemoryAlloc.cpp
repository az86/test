#include <iostream>
#include <algorithm>
using namespace std;

void ExceptionCheck();
void NullptrCheck();

int main()
{
	ExceptionCheck();
	// �����пռ�鲻̫���ã�����΢��ٷ��ĵ���������ôһ�λ��� ��������Ҫ����ʲô����ѡ����û������
	// If unsuccessful, new returns zero or throws an exception;
	// see The new and delete Operators for more information. 
	// You can change this default behavior by writing a custom 
	// exception-handling routine and calling the _set_new_handler run-time 
	// library function with your function name as its argument.
//	NullptrCheck();
}

void ExceptionCheck()
{
	const int allocCount = 1024;

	int *ps[allocCount] = {nullptr};

	try
	{
		const int allocSize = 16 * 1024 * 1024;
		for (int i = 0; i != allocCount; ++i)
		{
			ps[i] = new int [allocSize];
			cout << i  << " success "<< endl;
		}
	}
	catch(bad_alloc &e)
	{
		cerr << e.what() << endl;
		for (int i = 0; i != allocCount; ++i)
		{
			delete[]ps[i];
			ps[i] = nullptr;
		}
	}
}

void NullptrCheck()
{
	const int allocCount = 1024;
	const int allocSize = 16 * 1024 * 1024;

	int *ps[allocCount] = {nullptr};
	for (int i = 0; i != allocCount; ++i)
	{
		ps[i] = new(nothrow) int [allocSize];
		if (ps[i] == nullptr)
		{
			cerr << i << " unsuccessful" << endl;
			goto RELEASE;
		}
	}

RELEASE:
	for (int i = 0; i != allocCount; ++i)
	{
		delete[]ps[i];
		ps[i] = nullptr;
	}
}