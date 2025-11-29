#pragma once 
#define _WIN32_WINNT 0x0A00
#include <boost/asio.hpp>
#include <string>
#include <cstdint>

class TCP_Client : public std::enable_shared_from_this<TCP_Client>
{
public:
	TCP_Client(boost::asio::io_context& io_context, std::string address_in, uint16_t port_in, std::string username_in);
	void Connect();
private:
	boost::asio::ip::tcp::socket socket;
	boost::asio::ip::tcp::endpoint endpoint;
	std::string username;
};