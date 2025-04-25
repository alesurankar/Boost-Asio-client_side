#include <boost/asio.hpp>   // Include Boost.Asio for networking
#include <iostream>         // For std::cout

int main() {
    using namespace boost::asio;
    io_context io;                 // 1.Main I/O context for asynchronous operations

    ip::tcp::socket socket(io);    // 1.Create a socket for the client
    socket.connect(ip::tcp::endpoint(ip::make_address("127.0.0.1"), 1234)); // 1.Connect to the server

    char welcome[128];       // 2.Receive welcome message from server
    size_t id_len = socket.read_some(buffer(welcome));
    std::cout << std::string(welcome, id_len); // 2.Print assigned client ID

    std::string msg = "Hello From Client!";      // 1.Message to send to the server
    write(socket, buffer(msg));             // 1.Send the message

    char reply[128];                                              // 1.Buffer for the server's reply
    size_t len = socket.read_some(buffer(reply));                 // 1.Read server response
    std::cout << "Server Replyed: " << std::string(reply, len) << "\n";    // 1.Print the response
}