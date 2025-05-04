#include "ChatClient.h"
#include "App.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>


int main() 
{
    std::atomic<bool> running{ true };

    std::shared_ptr<MessageHandler> msgHandler = std::make_shared<MessageHandler>();
    App app(msgHandler);
    
    std::ifstream file("C:/Projects/Python_API_setup_for_NinjaStrike/username.txt");
    std::string username; 
    if (file.is_open())
    {
        std::getline(file, username);
    }
    
    boost::asio::io_context io; 
    auto client = std::make_shared<ChatClient>(io, "127.0.0.1", 1234, username, msgHandler);
    boost::asio::post(io, [client]()
        {
            client->Start();
        });
    std::thread networking([&]()
        {
            try
            {
                io.run();
            }
            catch (const std::exception& e)
            {
                std::cerr << "Exception in io.run(): " << e.what() << "\n";
            }
        });

    while (running)
	{
        app.Go();
	}
    
    networking.join();
    return 0;
}

//1. AppClient(input) -> 
//2. MSGClient(middleman) -> 
//3. Client(TCP) -> 
//4. Server(TCP) -> 
//5. MSGServer(middleman) -> 
//6. AppServer(updateParameters) -> 
//7. MSGServer(middleman) -> 
//8. Server(TCP) -> 
//9. Client(TCP) ->
//10. MSGClient(middleman) ->
//11. AppClient(displayOutput)