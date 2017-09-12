#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
using namespace boost;
using namespace boost::asio::ip;
int main()
{
	asio::io_service ioService;
	udp::socket sock(ioService, udp::endpoint(udp::v4(), 9999));

	int i;
	auto abc = boost::asio::buffer(&i, 4);
	udp::endpoint remote_endpoint;

	while (true)
	{
		sock.receive_from(abc, remote_endpoint);
		std::cout << i << std::endl;
	}
	return 0;
}