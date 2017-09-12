#include <vector>
#include <iostream>
#include <ctime>
using namespace std;

#include "../../BreezeJoeLib/Az/zfunctions.h"
using namespace az;
const int TestTimes = 10000;
void VecPreform();

template<typename T>
inline void SetValues(T p, int rowCount, int colCount)
{
	for (int ti = 0; ti != TestTimes; ++ti)
	{
		for (int row = 0; row != rowCount; ++row )
		{
			for (int col = 0; col != colCount; ++col)
			{
				p[row][col] = ti;
			}
		}
	}
}

double gVal;
template<typename T>
inline void GetValues(T p, int rowCount, int colCount)
{
	
	for (int ti = 0; ti != TestTimes; ++ti)
	{
		for (int row = 0; row != rowCount; ++row )
		{
			for (int col = 0; col != colCount; ++col)
			{
				gVal = p[row][col];
			}
		}
	}
}
void VecPreform()
{
	const int imRowsCount = 512;
	const int imColsCount = 512;
	typedef double DT;

	auto p = znew<DT>(imRowsCount, imColsCount);
	auto ts = clock();
	SetValues(p, imRowsCount, imColsCount);
	auto te = clock();
	cout << "array set value: " << te - ts << endl;

	ts = clock();
	GetValues(p, imRowsCount, imColsCount);
	te = clock();
	cout << "array get value: " << te - ts << endl;
	zdelete(p, imRowsCount);

	vector<vector<DT>> vec(imRowsCount, vector<DT>(imColsCount, 0));
	ts = clock();
	SetValues(vec, imRowsCount, imColsCount);
	te = clock();
	cout << "vector set value: " << te - ts << endl;

	ts = clock();
	GetValues(vec, imRowsCount, imColsCount);
	te = clock();
	cout << "vector get value: " << te - ts << endl;
}