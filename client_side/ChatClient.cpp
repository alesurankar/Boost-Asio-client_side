#include "ChatClient.h"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <atomic>

using namespace boost;

ChatClient::ChatClient(asio::io_context& io_in, const std::string& host_in, unsigned short port_in, const std::string& username_in)
    :
    socket(io_in),
    username(username_in)
{
    Connect(host_in, port_in);
}

void ChatClient::Start()
{
    SendUsername();
    Listen();
    SendMessages();
    Shutdown();
}

void ChatClient::Connect(const std::string& host, unsigned short port)
{
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(host), port);
    socket.connect(endpoint);
}

void ChatClient::SendUsername()
{
    asio::write(socket, asio::buffer(username + "\n"));
}

void ChatClient::Listen()
{
    std::thread([this]()
        {
            try {
                while (true)
                {
                    char buffer[512];
                    boost::system::error_code error;
                    size_t length = socket.read_some(asio::buffer(buffer), error);
                    if (error)
                    {
                        std::cerr << "Error reading message: " << error.message() << "\n";
                        break;
                    }
                    std::cout << "Received message: " << std::string(buffer, length) << "\n";
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Listen thread error: " << e.what() << "\n";
            }
        }).detach();
}

void ChatClient::SendMessages()
{
    std::string message;
    while (true) {
        std::getline(std::cin, message);
        if (message == "/exit") break;
        asio::write(socket, asio::buffer(message + "\n"));
    }
}

void ChatClient::Shutdown()
{
    try
    {
        socket.cancel();
        socket.shutdown(asio::ip::tcp::socket::shutdown_both);
    }
    catch (const system::system_error& e)
    {
        std::cout << "Shutdown failed: " << e.what() << "\n";
    }
    socket.close();
}
