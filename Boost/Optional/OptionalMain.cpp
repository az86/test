#include <iostream>
#include <string>
#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>

class CRefTest
{
	std::string m_name;

public:
	CRefTest(const std::string &name) : m_name(name) { std::cout << "Construct CRefTest " << m_name << std::endl; }
	CRefTest(const CRefTest &o) : m_name(o.m_name) { std::cout << "Construct CRefTest by & " << m_name << std::endl; }
	CRefTest(const CRefTest &&o) : m_name(o.m_name) { std::cout << "Construct CRefTest by && " << m_name << std::endl; }
	~CRefTest() { std::cout << "Destruct CRefTest " << m_name << std::endl; }
	void Output() { std::cout << "Output " << m_name << std::endl; }
};

int main()
{
	const double val = -10;

	// C++0x
	double rval = sqrt(val);
	if (_isnan(rval))
		std:: cout << rval << std::endl;

	// optional
	boost::optional<double> op0 (val > 0, sqrt(val));
	std:: cout << op0.get_value_or(DBL_EPSILON) << std::endl;

	// make_optional
	auto op1 = boost::make_optional(5);
	auto op2 = boost::make_optional<double>(val > 0, sqrt(val));
	//assert(op2);
	
	// in_place
	{ boost::optional<CRefTest> opo(boost::in_place(CRefTest("opo"))); }
	{ boost::optional<CRefTest> opo0x(CRefTest("C++0x use rval reference")); }

	return 0;
}