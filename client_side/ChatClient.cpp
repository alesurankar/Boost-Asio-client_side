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
