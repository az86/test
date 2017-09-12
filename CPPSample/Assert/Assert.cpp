#include <cassert>
#include <iostream>
using namespace std;
int main()
{
	int pEnd = 7;
	for (int i = 0; i != pEnd; i+=2 )
	{
		assert(i < pEnd);
	}
}
