// client.cpp
#include <boost/asio.hpp>

int main() {
    using namespace boost::asio;
    io_context io;

    ip::tcp::socket socket(io);
    socket.connect(ip::tcp::endpoint(ip::make_address("127.0.0.1"), 1234));

    std::string msg = "Hello Server!";
    write(socket, buffer(msg));
}
