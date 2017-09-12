#include <iostream>
using namespace	std;
#include <typeinfo>
#include <algorithm>

int main()
{
	// ����ͼ��512��&256�У����³����������д���
	const int colCount = 256;
	const int rowCount = 512;
	typedef double Pixel;

	// ��������ڴ����
	Pixel (*p)[colCount] = new Pixel[rowCount][colCount];
	cout << "p's type is " << typeid(p).name() << ", single row element size{count*size(ElementType)} is " << sizeof(p[1]) << endl;
	delete[] p;

	// ���Ų����ڴ����
	typedef Pixel RowElement[colCount];
	RowElement *pdr = new RowElement[rowCount];
	cout << "pdr's type is " << typeid(pdr).name() << ", single row element size{count*size(ElementType)} is " << sizeof(pdr[1]) << endl;
	delete[]pdr;

	// Ŀǰ�õıȽ϶�����ڴ�Ĵ���
	Pixel **pm = new Pixel *[rowCount];
	for_each(pm, pm + rowCount, [colCount, rowCount](Pixel * &dp){dp = new Pixel[colCount];});
	// lamada���ʽ��[]�еı����ڱ��ʽ{}�пɼ���
	// Pixel * & dp ��˵dp��PixelPointer*���͵ı������Ҵ������������ֵ���ȼ������ŵ�Ĵ�������(������ͷſ����Կ�)
	// typedef Pixel *PixelPointer;
	// for_each(pm, pm + rowCount, [colCount](PixelPointer &dp){dp = new Pixel[colCount];});

	// �ͷ��ڴ����
	for_each(pm, pm + rowCount, [](Pixel * const & dp){delete[]dp;});
	delete[]pm;

	return 0;
}