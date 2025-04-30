#pragma once
#include "MessageHandler.h"
#include <boost/asio.hpp>
#include <iostream>  
#include <string>
#include <atomic>
#include <mutex>

class ChatClient {
public:
    ChatClient(boost::asio::io_context& io_in, const std::string& host_in, unsigned short port_in, const std::string& username_in);
    void Start();
private:
    void Connect(const std::string& host, unsigned short port);
    void SendUsername();
    void Listen();
    void SendMessages();
    void Shutdown();
private:
    MessageHandler msg;
    std::mutex mtx;
    boost::asio::ip::tcp::socket socket;
    std::string username; 
};