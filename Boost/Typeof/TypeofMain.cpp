#include <iostream>
#include <typeinfo>
#include <boost/typeof/typeof.hpp>

int main()
{
	BOOST_AUTO(x, 2.0 * 3);			// obsoleted. C++0x auto.
	std::cout << typeid(x).name() << std::endl;
	return 0;
}