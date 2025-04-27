#include "ChatClient.h"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("C:/Projects/Python_API_setup_for_NinjaStrike/username.txt");
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