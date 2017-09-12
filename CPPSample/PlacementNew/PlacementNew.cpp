#include <new>
#include <iostream>
using namespace std;

class A
{
public:
	A(){}
	A(int a) :a(a){}
protected:
	int a;
};

class B : public A
{
public:
	B(int a, int b):A(a), b(b){} // call construct function A
	void Print()
	{
		cout << "a = " << a << ", b = " << b << endl;
	}
private:
	int b;
};

class C : public A
{
public:
	C(int a, int c): c(c){ new(this)A(a); }  // same to B
	void Print()
	{
		cout << "a = " << a << ", c = " << c << endl;
	}
private:
	int c;
};
int main()
{
	B b(2,5);
	b.Print();
	C c(3, 5);
	c.Print();

	int i = 0; 
	new (&i)int(99); // need header <new>
	cout << i << endl;
	return 0;
}