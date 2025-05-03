#pragma once
#include "MessageHandler.h"
#include <boost/asio.hpp>
#include <iostream>  
#include <string>
#include <atomic>
#include <mutex>

class ChatClient : public std::enable_shared_from_this<ChatClient>
{
public:
    ChatClient(boost::asio::io_context& io_in, const std::string& host_in, unsigned short port_in, const std::string& username_in, std::shared_ptr<MessageHandler> handler);
    void Start();
private:
    void SendUsername();
    void ReceiveMessages();
    void CheckAndSendMessage();
    void Shutdown();
private:
    std::shared_ptr<MessageHandler> msgHandler;
    std::mutex mtx;
    boost::asio::ip::tcp::socket socket;
    std::string username;
    std::queue<std::string> command_queue;
    boost::asio::streambuf buffer_;
    std::string host;
    unsigned short port; 
    boost::asio::steady_timer message_timer; 

};