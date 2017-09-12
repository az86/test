#include <iostream>
#include <algorithm>
using namespace std;

struct Pic2D
{
	Pic2D(short * const pPixelData, int width, int height)
		: m_pPixelData(pPixelData)
		, m_width(width)
		, m_height(height)
	{
	}

	short * const operator[](int index) const
	{
		return m_pPixelData + index * m_width;
	}
private:
	short * const m_pPixelData;
	int m_width;
	int m_height;
};

struct Pic3D
{
	Pic3D(Pic2D * const pPics, int lCount)
		: m_pPics(pPics)
		, m_count(lCount)
	{
	}

	Pic2D & operator[](int index) const
	{
		return m_pPics[index];
	}
private:
	Pic2D * const m_pPics;
	int m_count;
};

int main()
{
	const int width = 100;
	const int height = 100;
	auto pixelData = new short[width * height];

	auto index = 0;
	for_each(pixelData, pixelData + width * height, [&index](short &val){val = index++;} );

	Pic2D pic(pixelData, width, height);
	cout << "pic[50][50] = " << pic[50][50] << endl;
	delete[]pixelData;
	return 0;
}
