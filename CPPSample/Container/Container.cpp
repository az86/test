#include <vector>
#include <algorithm>
#include <iostream>
#include <typeinfo>
using namespace std;

#include "../../BreezeJoeLib/Az/zfunctions.h"
using namespace az;

template <class T>
vector<vector<T>> WorkFunc(const T * const * const p, const int &imRowsCount, const int &imColsCount)
{
	vector<vector<T>> imRows;
	// �Ӷ�ά�����ʼ��vector�����¼��бȽ���Ҫ
	for_each(p, p + imRowsCount, [imColsCount, &imRows](const T * const pd)
	{
		vector<T> imCol(pd, pd+imColsCount);
		imRows.push_back(move(imCol));
	});
	return move(imRows);
}


int main()
{
 	const int imRowsCount = 5;
 	const int imColsCount = 6;
	typedef int pixel;

	// ����ʼ��һ����ά���飬��ʵ���и��������������ͨ������������������
	auto p = znew<pixel>(imRowsCount, imColsCount);
	pixel tmp = 0;
	for_each(p, p + imRowsCount, [&tmp, imColsCount](pixel * const pd)
	{
		pixel &tmp(tmp);
		for_each(pd, pd + imColsCount, [&tmp](pixel&val){val = tmp++;});
	});

	auto imRows = WorkFunc((pixel**)p, imRowsCount, imColsCount);
	zdelete(p, imRowsCount);
	
	// ִ�����
	for_each(imRows.begin(), imRows.end(), [](vector<pixel> &imCol)
	{
		auto last = remove_if(imCol.begin(), imCol.end(), [](const pixel &val){return 0==val%2;});
		imCol.resize(last - imCol.begin());
		for_each(imCol.begin(), imCol.end(), [](const pixel&val){cout << val << '\t';});
		cout << endl;
	});
	return 0;
}
