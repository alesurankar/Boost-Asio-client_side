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
    std::cout << "Enter your username to join the chat: ";
    std::getline(std::cin, username);
    write(socket, buffer(username + "\n"));

    // Start listener thread to receive messages
    std::thread listener([&socket]()
        {
            try
            {
                boost::asio::streambuf buf;
                boost::system::error_code ec;
                while (true)
                {
                    boost::asio::read_until(socket, buf, '\n', ec);
                    if (ec)
                    {
                        std::cout << "Disconnected from server.\n";
                        break;
                    }
                    std::istream is(&buf);
                    std::string line;
                    std::getline(is, line);
                    if (!line.empty())
                    {
                        std::cout << line << "\n";
                    }
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "Listener error: " << e.what() << "\n";
            }
        });

    // Main thread: send messages from user input
    std::string msg;
    while (std::getline(std::cin, msg))
    {
        if (msg == "exit") break;
        write(socket, buffer(msg + "\n"));
    }

    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket.close();
    listener.join();
}