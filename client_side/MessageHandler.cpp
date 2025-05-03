#include "MessageHandler.h"
#include <iostream>


MessageHandler::MessageHandler()
{}


void MessageHandler::AppToMSG(const std::string& message)  //2. MSGClient(middleman)
{
    std::cout << "MessageHandler::AppToMSG: " << message << "//2. MSGClient(middleman)\n";
    std::lock_guard<std::mutex> lock(mtx);
    app_messages.push(message);
    std::cout << "Pushed message: " << message << "\n";
}


std::string MessageHandler::MSGToClient()  //3. Client(TCP)
{
    std::cout << "MessageHandler::MSGToClient::Queue size : " << app_messages.size() << "//3. Client(TCP)\n";
    std::lock_guard<std::mutex> lock(mtx);
    if (!app_messages.empty())
    {
        std::string msg = app_messages.front();
        app_messages.pop();
        std::cout << "Popped message: " << msg << "\n";

        return msg;
    }
    return "";
}


void MessageHandler::ClientToMSG(int x, int y) //10. MSGClient(middleman)
{
    std::cout << "MessageHandler::ClientToMSG: x = " << x << ", y = " << y << "//10. MSGClient(middleman)\n";
    std::lock_guard<std::mutex> lock(mtx);
	app_position.push(std::make_pair(x, y));
}


std::pair<int, int> MessageHandler::MSGToApp()
{
    std::cout << "MessageHandler:MSGToApp:\n";
    std::lock_guard<std::mutex> lock(mtx);

    auto pos = app_position.front();
    app_position.pop();
    return pos;
}