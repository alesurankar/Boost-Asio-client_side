#pragma once 
#define _WIN32_WINNT 0x0A00
#include <boost/asio.hpp>
#include <string>
#include <cstdint>

class TCP_Client
{
public:
	TCP_Client(boost::asio::io_context& io_context, std::string address_in, uint16_t port_in);
	void Connect();
private:
	boost::asio::io_context& io;
	std::string address;
	uint16_t port;
};