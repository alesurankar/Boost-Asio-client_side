#include "ChatClient.h"

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
    listener_thread = std::thread([this]() { Listen(); });
    SendMessages();
    listener_thread.join();
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
    try 
    {
        while (true)
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!running)
            {
                break;
            }
            asio::streambuf buf;
            system::error_code ec;
            asio::read_until(socket, buf, "\n", ec);
            if (ec)
            {
                if (ec == asio::error::eof || ec == asio::error::operation_aborted)
                {
                    break;
                }
                else
                {
                    std::cerr << "Listen error: " << ec.message() << "\n";
                    break;
                }
            }
            std::istream is(&buf);
            std::string message;
            std::getline(is, message);
            if (!message.empty())
            {
                std::cout << message << "\n";
            }
        }
    }
    catch (...)
    {
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
            running = false;
            system::error_code ignored_ec;
            socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
            break;
        }
        if (socket.is_open())
        {
            asio::write(socket, asio::buffer(msg + "\n"));
        }
        else 
        {
            std::cout << "Socket is closed. Cannot send message.\n";
            break;
        }
    }
}


void ChatClient::Shutdown()
{
    try
    {
        socket.shutdown(asio::ip::tcp::socket::shutdown_both);
    }
    catch (const system::system_error& e)
    {
        std::cout << "Shutdown failed: " << e.what() << "\n";
    }
    socket.close();
    if (listener_thread.joinable())
    {
        listener_thread.join();
    }
}
