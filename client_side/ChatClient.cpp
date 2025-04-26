#include "ChatClient.h"

ChatClient::ChatClient(boost::asio::io_context& io, const std::string& host, unsigned short port)
    : 
    socket_(io)
{
    Connect(host, port);
}

void ChatClient::Start()
{
    SendUsername();
    listener_thread_ = std::thread([this]() { Listen(); });
    SendMessages();
    Shutdown();
}


void ChatClient::Connect(const std::string& host, unsigned short port)
{
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(host), port);
    socket_.connect(endpoint);
}

void ChatClient::SendUsername()
{
    std::cout << "Enter your username to join the chat: ";
    std::getline(std::cin, username_);
    boost::asio::write(socket_, boost::asio::buffer(username_ + "\n"));
}

void ChatClient::Listen()
{
    try
    {
        boost::asio::streambuf buf;
        boost::system::error_code ec;
        while (true)
        {
            boost::asio::read_until(socket_, buf, '\n', ec);
            if (ec)
            {
                std::cout << "Disconnected from server.\n";
                break;
            }
            std::istream is(&buf);
            std::string line;
            std::getline(is, line);
            if (!line.empty())
            {
                std::cout << line << "\n";
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Listener error: " << e.what() << "\n";
    }
}

void ChatClient::SendMessages()
{
    std::string msg;
    while (std::getline(std::cin, msg))
    {
        if (msg == "exit") break;
        boost::asio::write(socket_, boost::asio::buffer(msg + "\n"));
    }
}

void ChatClient::Shutdown()
{
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket_.close();
    if (listener_thread_.joinable())
        listener_thread_.join();
}
