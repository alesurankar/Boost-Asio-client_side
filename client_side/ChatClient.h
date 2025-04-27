#pragma once
#include <boost/asio.hpp>
#include <iostream>         
#include <thread>
#include <string>
#include <atomic>

class ChatClient {
public:
    ChatClient(boost::asio::io_context& io, const std::string& host, unsigned short port, const std::string& username);
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
    std::atomic<bool> running_{ true };
};