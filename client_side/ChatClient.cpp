#include "ChatClient.h"

using namespace boost;

ChatClient::ChatClient(asio::io_context& io_in, const std::string& host_in, unsigned short port_in, const std::string& username_in, std::shared_ptr<MessageHandler> handler)
    :
    socket(io_in),
    username(username_in),
    host(host_in),
    port(port_in),
    message_timer(io_in),
    msgHandler(handler)
{}

void ChatClient::Start()
{
    std::cout << "ChatClient::Start\n";
    auto self = shared_from_this();
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(host), port);

    socket.async_connect(endpoint, [this, self](boost::system::error_code ec) 
        {
            if (!ec)
            {
                SendUsername();
                ReceiveMessages();
                CheckAndSendMessage();
            }
            else
            {
                std::cerr << "Connect failed: " << ec.message() << "\n";
            }
        });
}


void ChatClient::SendUsername()
{
    std::cout << "ChatClient::SendUsername: "<< username << "\n";
    asio::write(socket, asio::buffer(username + "\n"));
}


void ChatClient::ReceiveMessages()
{
    std::cout << "ChatClient::ReceiveMessages:\n";
    auto self(shared_from_this());

    boost::asio::async_read_until(socket, buffer_, '\n',

        [this, self](boost::system::error_code ec, std::size_t length)
        {
            try
            {
                if (!ec)
                {
                    std::istream is(&buffer_);
                    std::string message;
                    std::getline(is, message);

                    //buffer_.consume(length);

                    std::cout << "Received: " << message << "\n";

                    int x, y;
                    std::istringstream iss(message);
                    if (iss >> x >> y)
                    {
                        msgHandler->ClientToMSG(x, y);
                    }
                    else
                    {
                        std::cout << "Failed to parse coordinates from message.\n";
                    }


                    ReceiveMessages();
                }
                else
                {
                    Shutdown();
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Async handler exception in ReceiveMessages: " << e.what() << "\n";
            }
        });
}


void ChatClient::CheckAndSendMessage()
{
    std::cout << "ChatClient::CheckAndSendMessage:\n";
    auto self = shared_from_this();
    std::string message = msgHandler->MSGToClient();
    
    if (!message.empty())
    {
        std::cout << "ChatClient::CheckAndSendMessage: Writing: " << message << "\n";
        boost::asio::async_write(socket, boost::asio::buffer(message + "\n"),
            [this, self](boost::system::error_code ec, std::size_t)
            {
                if (ec)
                {
                    std::cerr << "Send error: " << ec.message() << "\n";
                    Shutdown();
                    return;
                }
    
                CheckAndSendMessage();
            });
    }
}


void ChatClient::Shutdown()
{
    std::cout << "ChatClient::Shutdown:\n";
    try
    {
        socket.cancel();
        socket.shutdown(asio::ip::tcp::socket::shutdown_both); 
        message_timer.cancel();
    }
    catch (const system::system_error& e)
    {
        std::cout << "Shutdown failed: " << e.what() << "\n";
    }
    socket.close();
}
