#include "ChatClient.h"

int main()
{
    boost::asio::io_context io;
    ChatClient client(io, "127.0.0.1", 1234);
    client.Start();
}