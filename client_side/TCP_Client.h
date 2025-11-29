#pragma once 
#define _WIN32_WINNT 0x0A00
#include <boost/asio.hpp>

class TCP_Client
{
public:
	TCP_Client(boost::asio::io_context& io_context);
	void Connect();
private:
};