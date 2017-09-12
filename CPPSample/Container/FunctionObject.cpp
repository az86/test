#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

template<typename DT>
class TTT : public binary_function<DT, DT, void>
{
public:
	void operator()(const DT& _Left, const DT & _Right) const
	{
		cout << _Left << ',' << _Right << endl;
	}
};

void TestFunc()
{
	int vec[] = {1, 2, 3, 4, 5, 6};
	for_each(vec, vec + 6, bind2nd(TTT<int>(), 911));
//	for_each(vec, vec + 6, bind2nd(CCC, 911));
}