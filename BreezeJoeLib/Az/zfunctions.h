#pragma once
#include <algorithm>
namespace az
{
	template<typename T>
	T** znew(size_t row, size_t col)
	{
		T** rVal = new T*[row];
		std::for_each(rVal, rVal + row, [col](T*&val){val = new T[col];});
		return rVal;
	}

	template<typename T>
	void zdelete(T**pDest, const size_t row)
	{
		std::for_each(pDest, pDest + row, [](T*&val){delete[] val;});
		delete[] pDest;
	}
}
