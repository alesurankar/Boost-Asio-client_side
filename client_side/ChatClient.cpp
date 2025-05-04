#include "ChatClient.h"
#include <chrono>
#include <thread>

using namespace boost;

ChatClient::ChatClient(asio::io_context& io_in, const std::string& host_in, unsigned short port_in, const std::string& username_in, std::shared_ptr<MessageHandler> msgHandler_in)
    :
    socket(io_in),
    username(username_in),
    host(host_in),
    port(port_in),
    msgHandler(msgHandler_in),
    timer(io_in)
{}


void ChatClient::Start()
{
    std::cout << "NetworkingThread::ChatClient::Start\n\n";
    auto self = shared_from_this();
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(host), port);

    socket.async_connect(endpoint, [this, self](boost::system::error_code ec) 
        {
            if (!ec)
            {
                //SendUsername();
                ReceiveMessages();
                CheckAndSend();
            }
            else
            {
                std::cerr << "Connect failed: " << ec.message() << "\n";
            }
        });
}


//void ChatClient::SendUsername()
//{
//    //std::string first_command = "UP";
//    //std::cout << "ChatClient::SendUsername: " << first_command << "\n";
//    //asio::write(socket, asio::buffer(first_command + "\n"));
//    std::cout << "ChatClient::SendUsername: "<< username << "\n";
//    asio::write(socket, asio::buffer(username + "\n"));
//}


void ChatClient::ReceiveMessages() //12. Client(TCP)
{
    auto self = shared_from_this();
    boost::asio::async_read_until(socket, input_buffer, '\n',    //12. Client(TCP)
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::istream is(&input_buffer);
                std::string msg;
                std::getline(is, msg);

                std::cout << "Step 12, ChatClient::ReadMessage::Received: " << msg << "\n";

                size_t commaPos = msg.find(',');
                if (commaPos != std::string::npos)
                {
                    try
                    {
                        int x = std::stoi(msg.substr(0, commaPos));
                        int y = std::stoi(msg.substr(commaPos + 1));
                        std::cout << "Step 12, converted: " << "x = " << x << ", y = " << y << "\n";
                        msgHandler->ClientToMSG(x, y); //13. MSGClient(middleman)
                    }
                    catch (const std::exception& e)
                    {
                        std::cout << "Failed to convert coordinates: " << e.what() << "\n";
                    }
                }
                else
                {
                    std::cout << "Invalid coordinate format: " << msg << "\n";
                }
                ReceiveMessages();
            }
            else
            {
                //Shutdown();
            }
        });
    std::cout << "Step 12--------------\n";
}


void ChatClient::CheckAndSend() //3. Client(TCP)
{
    //std::cout << "ChatClient::CheckAndSendMessage: " << ", Step 3. Client(TCP)\n";
    auto self = shared_from_this();
    msg = msgHandler->MSGToClient();   //3. Client(TCP)
    if (!msg.empty())
    {
        boost::asio::async_write(socket, boost::asio::buffer(msg),
            [this, self](const boost::system::error_code& ec, std::size_t)
            {
                if (!ec)
                {
                    std::cout << "Step 4: NetworkingThread::ChatClient::CheckAndSendMessage: " << msg;
                }
                else
                {
                    std::cerr << "Send error: " << ec.message() << "\n";
                    //Shutdown();
                    return;
                }
                boost::asio::post(socket.get_executor(), [this, self]() {
                    CheckAndSend();
                    });
                std::cout << "Step4--------------\n";
            });
    }
    else
    {
        timer.expires_after(std::chrono::milliseconds(100));
        timer.async_wait([this, self](boost::system::error_code ec)
            {
                if (!ec)
                {
                    CheckAndSend();
                }
            });
    }
}


//void ChatClient::Shutdown()
//{
//    std::cout << "ChatClient::Shutdown:\n";
//    try
//    {
//        socket.cancel();
//        socket.shutdown(asio::ip::tcp::socket::shutdown_both); 
//    }
//    catch (const system::system_error& e)
//    {
//        std::cout << "Shutdown failed: " << e.what() << "\n";
//    }
//    socket.close();
//}
