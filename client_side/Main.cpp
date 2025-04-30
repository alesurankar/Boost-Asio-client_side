#include "ChatClient.h"
#include "App.h"
#include <iostream>
#include <fstream>
#include <thread>


int main() 
{
    //App app; 
    
    std::ifstream file("C:/Projects/Python_API_setup_for_NinjaStrike/username.txt");
    std::string username; 
    if (file.is_open())
    {
        std::getline(file, username);
    }
    
    boost::asio::io_context io;
    ChatClient client(io, "127.0.0.1", 1234, username);
    //std::thread networking([&]()
    //    {
            client.Start();
            io.run();
    //    });

    //while (true)
	//{
    //    app.Go();
	//}
    
    //networking.join();
    return 0;
}

//App -> MSG -> Client -> Server -> Client -> MSG -> App