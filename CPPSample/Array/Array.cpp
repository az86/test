#include <iostream>
using namespace	std;
#include <typeinfo>
#include <algorithm>

int main()
{
	// 假设图像512行&256列，以下程序数据以行储存
	const int colCount = 256;
	const int rowCount = 512;
	typedef double Pixel;

	// 常规操作内存代码
	Pixel (*p)[colCount] = new Pixel[rowCount][colCount];
	cout << "p's type is " << typeid(p).name() << ", single row element size{count*size(ElementType)} is " << sizeof(p[1]) << endl;
	delete[] p;

	// 优雅操作内存代码
	typedef Pixel RowElement[colCount];
	RowElement *pdr = new RowElement[rowCount];
	cout << "pdr's type is " << typeid(pdr).name() << ", single row element size{count*size(ElementType)} is " << sizeof(pdr[1]) << endl;
	delete[]pdr;

	// 目前用的比较多操作内存的代码
	Pixel **pm = new Pixel *[rowCount];
	for_each(pm, pm + rowCount, [colCount, rowCount](Pixel * &dp){dp = new Pixel[colCount];});
	// lamada表达式中[]中的变量在表达式{}中可见。
	// Pixel * & dp 是说dp是PixelPointer*类型的变量并且传入变量的引用值，等价且优雅点的代码如下(你可以释放开试试看)
	// typedef Pixel *PixelPointer;
	// for_each(pm, pm + rowCount, [colCount](PixelPointer &dp){dp = new Pixel[colCount];});

	// 释放内存代码
	for_each(pm, pm + rowCount, [](Pixel * const & dp){delete[]dp;});
	delete[]pm;

	return 0;
}