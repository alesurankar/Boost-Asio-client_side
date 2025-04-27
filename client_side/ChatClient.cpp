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
    asio::streambuf buf;
    system::error_code ec;

    // Start asynchronous read operation
    asio::async_read_until(socket, buf, "\n",
        [this, &buf](system::error_code ec, std::size_t bytes_transferred)
        {
            if (ec)
            {
                if (ec == asio::error::eof || ec == asio::error::operation_aborted)
                {
                    std::cout << "Connection closed or operation aborted.\n";
                }
                else
                {
                    std::cerr << "Listen error: " << ec.message() << "\n";
                }
                return;
            }

            std::istream is(&buf);
            std::string message;
            std::getline(is, message);
            if (!message.empty())
            {
                std::cout << message << "\n";
            }

            Listen();
        });
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
}
