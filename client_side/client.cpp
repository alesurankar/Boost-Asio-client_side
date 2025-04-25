#include <boost/asio.hpp> 
#include <iostream>         
#include <thread>    //3.
#include <string>    //3.

int main() {
    using namespace boost::asio;
    io_context io;           

    ip::tcp::socket socket(io);
    socket.connect(ip::tcp::endpoint(ip::make_address("127.0.0.1"), 1234));

    std::thread listener([&socket]()
        {
            boost::asio::streambuf buf; // 3.
            boost::system::error_code ec;
            while (true)
            {
                boost::asio::read_until(socket, buf, '\n', ec); // 3. Wait until newline
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
        if (msg == "exit") break;               // 3.
        write(socket, buffer(msg + "\n"));  
    }

    socket.close();  // 3. Close socket when done
    listener.join(); // 3. Wait for listener to finish
}