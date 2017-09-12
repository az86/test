#include <iostream>
using namespace std;
#include <ctime>
#include <algorithm>

const int testTime  = 500;
typedef double *pdouble;

void Array1D(int m, int n);
void Array2DVirtual(int m, int n);
void Array2D(int m, int n);

void Remainder(int m, int n);
void Divide(int m, int n);
void Multiply(int m, int n);
int main()
{
	const int length = 1024;
// 	Array1D(length, length);
// 	Array2D(length, length);
// 	Array2DVirtual(length, length);

	Multiply(length, length);
	Divide(length ,length);
	Remainder(length, length);
	cout << endl;

// 	Array1D(length, length);
// 	Array2D(length, length);
// 	Array2DVirtual(length, length);

	Multiply(length, length);
	Divide(length ,length);
	Remainder(length, length);
	cout << endl;

// 	Array1D(length, length);
// 	Array2D(length, length);
// 	Array2DVirtual(length, length);

	Multiply(length, length);
	Divide(length ,length);
	Remainder(length, length);
	cout << endl;
	return 0;
}

void Array1D(int m, int n)
{
	pdouble p = new double[m*n];
	auto tS = clock();
	for (int k = 0; k != testTime; ++k)
	{
		for (int i = 0; i != m - 5; ++i)
		{
			for (int j = 0; j != n; ++j)
			{
				p[i * n + j] = 5;
				p[(i+1) * n +j] = p[i*n+j] * 5;
				p[(i+2) * n +j] = p[i*n+j] * 6;
				p[(i+3) * n +j] = p[i*n+j] * 7;
				p[(i+4) * n +j] = p[i*n+j] * 8;
				p[(i+5) * n +j] = p[i*n+j] * 9;
			}
		}
	}
	auto tE = clock();
	cout << "array 1d: " << tE - tS << endl;
	delete[]p;
}

void Array2DVirtual(int m, int n)
{
	auto p1 = new double [n*m];
	auto p = new pdouble[m];
	for (int i = 0; i!=m; ++i)
	{
		p[i] = p1 + m * i;
	}

	auto tS = clock();
	for (int k = 0; k != testTime; ++k)
	{
		for (int i = 0; i != m - 5; ++i)
		{
			for (int j = 0; j != n; ++j)
			{
				p[i][j] = 5;
				p[i+1][j] = p[i][j] * 5;
				p[i+2][j] = p[i][j] * 6;
				p[i+3][j] = p[i][j] * 7;
				p[i+4][j] = p[i][j] * 8;
				p[i+5][j] = p[i][j] * 9;

			}
		}
	}
	auto tE = clock();
	cout << "array 2d virtual: " << tE - tS << endl;
	delete[]p;
	delete[]p1;
}

void Array2D(int m, int n)
{
	auto p = new pdouble[m];
	for (int i = 0; i!=m; ++i)
	{
		p[i] = new double[n];
	}
	auto tS = clock();
	for (int k = 0; k != testTime; ++k)
	{
		for (int i = 0; i != m - 5; ++i)
		{
			for (int j = 0; j != n; ++j)
			{
				p[i][j] = 5;
				p[i+1][j] = p[i][j] * 5;
				p[i+2][j] = p[i][j] * 6;
				p[i+3][j] = p[i][j] * 7;
				p[i+4][j] = p[i][j] * 8;
				p[i+5][j] = p[i][j] * 9;
			}
		}
	}
	auto tE = clock();
	cout << "array 2d: " << tE - tS << endl;
	for (int i = 0; i!=m; ++i)
	{
		delete[]p[i];
	}
	delete[]p;
}

typedef unsigned int ResultType;

void Remainder(int m, int n)
{
	ResultType a = 0;
	auto ts = clock();
	for (int k = 0; k != testTime; ++k)
	{
		for (int i = 0; i != m; ++i)
		{
			for (int j = 0; j != n; ++j)
			{
				 a += (i*j) % 9;
			}
		}
	}
	auto te = clock();
	cout << "%: " << te - ts << '\t' << a << endl;
}

void Multiply(int m, int n)
{
	ResultType a = 0;
	auto ts = clock();
	for (int k = 0; k != testTime; ++k)
	{
		for (int i = 0; i != m; ++i)
		{
			for (int j = 0; j != n; ++j)
			{
				a += (i*j) * 9;
			}
		}
	}
	auto te = clock();
	cout << "*: " << te - ts <<  '\t' << a <<endl;
}

void Divide(int m, int n)
{
	ResultType a = 0;
	auto ts = clock();
	for (int k = 0; k != testTime; ++k)
	{
		for (int i = 0; i != m; ++i)
		{
			for (int j = 0; j != n; ++j)
			{
				a += (i*j) / 9;
			}
		}
	}
	auto te = clock();
	cout << "/: " << te - ts <<  '\t' << a <<endl;
}