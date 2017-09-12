#include <iostream>
using namespace std;

#include "../BreezeJoeLib/BreezeJoeLib.h"
using namespace BreezeJoe;

#include "../Az/Matrix2D.h"
#include "../Az/zfunctions.h"
using namespace az;

int main()
{
	//POINT pts[4];
	//pts[0].x = 1;
	//pts[0].y = 1;

	//pts[1].x = 1;
	//pts[1].y = 3;

	//pts[2].x = 4;
	//pts[2].y = 3;

	//pts[3].x = 4;
	//pts[3].y = 1;

	//int len = 4;
	//vector<POINT> region;
	//bool res = GetRegionPnts(region,pts,len);


	const int rowCount = 4;
	const int colCount = 8;
	auto p = znew<double>(rowCount, colCount);
	//zdelete(p, rowCount);
	auto p1 = znew<double>(rowCount, colCount);;

	// 随便初始化俩矩阵的值
	for (int i = 0; i != rowCount; ++i)
	{
		for (int j = 0; j != colCount; ++j)
		{
			p1[i][j] = p[i][j] = i*8+j;
		}
	}

	// 执行加法
	CMatrix2D<double> m1(p, rowCount, colCount);
	m1 += CMatrix2D<double>(p1, rowCount, colCount);
	//执行输出
	for (int i = 0; i != rowCount; ++i)
	{
		for (int j = 0; j != colCount; ++j)
		{
			cout << p[i][j] << ',';
		}
		cout << endl;
	}

	return 0;
}