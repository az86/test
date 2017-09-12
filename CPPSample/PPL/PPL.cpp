#include <ppl.h>
using namespace Concurrency;
#include <iostream>
#include <vector>
using namespace std;

void For()
{
	combinable<size_t> counts;

	parallel_for<int>(0, 10, [&](const int &val)
	{
		counts.local()+= val;
		counts.local() *= 10;
		for (int i = 0; i != 100; ++i)
		{
			for (int j = 0; j != 0xFFFFFFF; ++j)
			{}
		}
	});
	int sum = counts.combine(plus<int>());

	cout << sum << endl;
}

void ForEach()
{
	vector<int> vec(10, 50);
	combinable<size_t> counts;

	parallel_for_each(vec.begin(), vec.end(), [&](int &val)
	{
		counts.local()+= val;
	});
	int sum = counts.combine(plus<int>());

	cout << sum << endl;
}
int main()
{
	ForEach();
	return 0;
}