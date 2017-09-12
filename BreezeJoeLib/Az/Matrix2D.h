#pragma once

#include <iterator>
using namespace stdext;

template<typename T>
class CMatrix2D
{
public:
	CMatrix2D(T **p, int row, int col) 
		: m_p(p)
		, m_row(row)
		, m_col(col)
	{

	}
	T **m_p;
	int m_row;
	int m_col;
};

template<typename T>
CMatrix2D<T>& operator +=(CMatrix2D<T> & pDest1,const CMatrix2D<T> & pDest2)
{
	std::transform(pDest1.m_p, pDest1.m_p + pDest1.m_row, pDest2.m_p, checked_array_iterator<T**>(pDest1.m_p,pDest1.m_row), [&pDest1](T *p1, T *p2)->T*
	{
		std::transform(p1, p1 + pDest1.m_col, p2,checked_array_iterator<T*>(p1, pDest1.m_col), std::plus<T>());
		return p1;
	});	
	return pDest1;
}
