#include "TCP_Client.h"
#include <utility>
#include <iostream>


TCP_Client::TCP_Client(boost::asio::io_context& io_context, std::string address, uint16_t port, std::string username_in)
	:
	socket(io_context),
	endpoint(boost::asio::ip::make_address(address), port),
	username(std::move(username_in))
{
}

void TCP_Client::Connect()
{
	std::cout << "TCP_Client::Connect:\n"; 
	auto self = shared_from_this();
    socket.async_connect(endpoint, [this,self](const boost::system::error_code& ec) {
        if (ec) {
            std::cerr << "Connect failed: " << ec.message() << "\n";
        }
        else {
            std::cout << "Connected to server!\n";
            // TODO: start async_read or async_write here
        }
        });
	std::cout << "--------------\n\n";
}