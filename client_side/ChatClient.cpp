#include "ChatClient.h"
#include <chrono>
#include <thread>

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


void ChatClient::ReceiveMessages() //9. Client(TCP)
{
    std::cout << "ChatClient::ReceiveMessages: " << "//9. Client(TCP)\n";
    auto self(shared_from_this());

    boost::asio::async_read_until(socket, buffer_, '\n', //8. Server(TCP)
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::istream is(&buffer_);
                std::string message;
                std::getline(is, message);

                std::cout << "Received: " << message << "\n";

                size_t commaPos = message.find(',');
                if (commaPos != std::string::npos)
                {
                    try
                    {
                        int x = std::stoi(message.substr(0, commaPos));
                        int y = std::stoi(message.substr(commaPos + 1));
                        msgHandler->ClientToMSG(x, y); //10. MSGClient(middleman)
                    }
                    catch (const std::exception& e)
                    {
                        std::cout << "Failed to convert coordinates: " << e.what() << "\n";
                    }
                }
                else
                {
                    std::cout << "Invalid coordinate format: " << message << "\n";
                }
                ReceiveMessages();
            }
            else
            {
                Shutdown();
            }
        });
}


void ChatClient::CheckAndSendMessage() //3. Client(TCP)
{
    std::cout << "ChatClient::CheckAndSendMessage: " << "//3. Client(TCP)\n";
    auto self = shared_from_this();
    std::string message = msgHandler->MSGToClient();  //3. Client(TCP)
    
    if (!message.empty())
    {
        std::cout << "ChatClient::CheckAndSendMessage: Writing: " << message << "\n";
        boost::asio::async_write(socket, boost::asio::buffer(message + "\n"), //4. Server(TCP)
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
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
