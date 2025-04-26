#include <boost/asio.hpp> 
#include <iostream>         
#include <thread>
#include <string>

int main() {
    using namespace boost::asio;
    io_context io;           

    ip::tcp::socket socket(io);
    socket.connect(ip::tcp::endpoint(ip::make_address("127.0.0.1"), 1234));

    // Send username first
    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);
    write(socket, buffer(username + "\n"));

    // Start listener thread to receive messages
    std::thread listener([&socket]()
        {
            boost::asio::streambuf buf;
            boost::system::error_code ec;
            while (true)
            {
                boost::asio::read_until(socket, buf, '\n', ec);
                if (ec) break;
                std::istream is(&buf);
                std::string line;
                std::getline(is, line);
                std::cout << "Server: " << line << "\n";
            }
        });

    // Main thread: send messages from user input
    std::string msg;
    while (std::getline(std::cin, msg))
    {
        if (msg == "exit") break;
        write(socket, buffer(msg + "\n"));
    }

    socket.close();
    listener.join();
}