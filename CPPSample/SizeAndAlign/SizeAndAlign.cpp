#include <iostream>
#include <memory>
#include <exception>
using namespace std;

__declspec(align(16)) struct T		//��16�ֽ�Ϊ��С��ŵ�Ԫ
{
	int i, j;
	T()
	{
		cout << "T is constructed~" << endl;
	}
	~T()
	{
		cout << "T is deconstructed!" << endl;
	}
};

void TestMemoryLeak(shared_ptr<T> ptr)
{
	throw exception();
}
#include <vector>
#include <algorithm>

int main()
{
	static_assert(sizeof(T) == 16, "error: az, size of T is not equal to 16");		// static_assert. if not ok. compile error!
	cout << "align of T is: " << __alignof(T) << endl;
	cout << "size of T is: " << sizeof(T) << endl;

	cout << endl;
	try
	{
		TestMemoryLeak(shared_ptr<T> (new T));
	}
	catch (exception &e)
	{
		cerr <<  "exception is caught, " << e.what() << endl;
	}
	return 0;
}