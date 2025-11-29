#include "TCP_Client.h"
#include <utility>
#include <iostream>

TCP_Client::TCP_Client(boost::asio::io_context& io_context, std::string address_in, uint16_t port_in)
	:
	io(io_context),
	address(std::move(address_in)),
	port(port_in)
{
}

void TCP_Client::Connect()
{
	std::cout << "TCP_Client::Connect:\n";

	std::cout << "--------------\n\n";
}