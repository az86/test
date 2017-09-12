#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include <boost/assign.hpp>


int main()
{
	vector<int> vec;
	vec.assign(5, 0); // C++0x
	
	{
		using namespace boost::assign;
		vec += 999, 777, 888, 555, 111;
	}

	for_each(vec.cbegin(), vec.cend(), [](const int &val) { cout << val << ", "; });
	return 0;
}