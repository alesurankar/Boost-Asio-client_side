#include <boost/asio.hpp>   // Include Boost.Asio for networking
#include <iostream>         // For std::cout

int main() {
    using namespace boost::asio;
    io_context io;                 // Main I/O context for asynchronous operations

    ip::tcp::socket socket(io);    // Create a socket for the client
    socket.connect(ip::tcp::endpoint(ip::make_address("127.0.0.1"), 1234)); // Connect to the server

    std::string msg = "Hello Server!";      // Message to send to the server
    write(socket, buffer(msg));             // Send the message

    char reply[128];                                              // Buffer for the server's reply
    size_t len = socket.read_some(buffer(reply));                 // Read server response
    std::cout << "Reply: " << std::string(reply, len) << "\n";    // Print the response
}