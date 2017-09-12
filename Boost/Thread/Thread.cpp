#define _WIN32_WINNT 0x0501
#include <boost/asio.hpp>
#include <boost/timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;
#include <iostream>
using namespace std;


int main()
{
	asio::io_service ios;
	asio::deadline_timer t(ios, posix_time::seconds(5));
	cout << t.expires_at() <<endl;
	t.wait();
	cout << get_system_time() << endl;
	cout << "hello asio" << endl;
	return 0;
}