#pragma once
#include <boost/asio.hpp> 
#include <iostream>         
#include <thread>
#include <string>

class ChatClient {
public:
    ChatClient(boost::asio::io_context& io, const std::string& host, unsigned short port);
    void Start();
private:
    void Connect(const std::string& host, unsigned short port);
    void SendUsername();
    void Listen();
    void SendMessages();
    void Shutdown();
private:
    boost::asio::ip::tcp::socket socket_;
    std::thread listener_thread_;
    std::string username_;
};