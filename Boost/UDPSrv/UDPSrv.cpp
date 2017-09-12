#include <iostream>
using namespace std;
#include <boost/asio.hpp>
using namespace boost;
using namespace boost::asio::ip;


void writeHandler(const system::error_code & co, size_t si)
{
	static int i = 0;
	cout << i++ <<" send msg comp " << co.message() << ",si = " << si<< endl;
}

asio::io_service ioService;
udp::socket sock(ioService, udp::endpoint(udp::v4(), 10000));

void Run(void *)
{
	boost::asio::io_service::work work(ioService);
	ioService.run();
}
int main()
{
	auto abc = 1024;
	auto buf = boost::asio::buffer(&abc, 4);
	sock.set_option(asio::socket_base::broadcast(true));
	boost::asio::ip::address addr = boost::asio::ip::address::from_string("255.255.255.255");
	udp::endpoint receiver_endpoint(addr, 9999);
	for (int i = 0; i != 1000; i++)
	{
		abc ++;
		sock.async_send_to(buf, receiver_endpoint, 0, writeHandler);
	}
	cout <<1234 <<  endl;
	char c;
	cin >> c;
	ioService.run();
	return 0;
}