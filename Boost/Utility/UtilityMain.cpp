#include <boost/utility.hpp>

class CDoNotCopy : public boost::noncopyable
{

};

int main()
{
	CDoNotCopy a;
	//CDoNotCopy b(a);		// error
	//CDoNotCopy c = a;		// error
}