#include "ChatClient.h"


ChatClient::ChatClient(boost::asio::io_context& io, const std::string& host, unsigned short port, const std::string& username)
    : 
    socket_(io), 
    username_(username)
{
    Connect(host, port);
}


void ChatClient::Start()
{
    SendUsername();
    listener_thread_ = std::thread([this]() { Listen(); });
    SendMessages();
    listener_thread_.join();
    Shutdown();
}

void ChatClient::Connect(const std::string& host, unsigned short port)
{
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(host), port);
    socket_.connect(endpoint);
}

void ChatClient::SendUsername()
{
    boost::asio::write(socket_, boost::asio::buffer(username_ + "\n"));
}

void ChatClient::Listen()
{
    try {
        while (running_)
        {
            boost::asio::streambuf buf;
            boost::system::error_code ec;
            boost::asio::read_until(socket_, buf, "\n", ec);
            if (ec) {
                if (ec == boost::asio::error::eof || ec == boost::asio::error::operation_aborted) {
                    break;  // Socket closed or operation aborted => exit cleanly
                }
                else {
                    std::cerr << "Listen error: " << ec.message() << "\n";
                    break;
                }
            }
            std::istream is(&buf);
            std::string message;
            std::getline(is, message);
            if (!message.empty())
                std::cout << message << "\n";
        }
    }
    catch (...) {
        std::cerr << "Exception in Listen thread\n";
    }
}


void ChatClient::SendMessages()
{
    std::string msg;
    while (std::getline(std::cin, msg))
    {
        if (msg == "exit")
        {
            running_ = false; // signal listen thread to stop
            boost::system::error_code ignored_ec;
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec); // wake up listener
            break;
        }
        if (socket_.is_open()) {
            boost::asio::write(socket_, boost::asio::buffer(msg + "\n"));
        }
        else {
            std::cout << "Socket is closed. Cannot send message.\n";
            break;
        }
    }
}


void ChatClient::Shutdown()
{
    try {
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    }
    catch (const boost::system::system_error& e) {
        std::cout << "Shutdown failed: " << e.what() << "\n";
    }
    socket_.close();

    if (listener_thread_.joinable())
        listener_thread_.join();
}
