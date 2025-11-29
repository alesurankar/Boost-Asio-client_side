#include "ChatClient.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <filesystem>

int main() {
    std::ifstream file("username.txt");
    std::string username;
    if (file.is_open())
    {
        std::getline(file, username);
    }

    boost::asio::io_context io;
    ChatClient client(io, "127.0.0.1", 1234, username);
    client.Start();
    return 0;
}