#include "MessageHandler.h"
#include <iostream>


MessageHandler::MessageHandler()
{}


void MessageHandler::AppToMSG(const std::string& message)
{
    //std::cout << "MessageHandler::AppToMSG: " << message << "\n";
    std::lock_guard<std::mutex> lock(mtx);
    app_messages.push(message);
    std::cout << "Pushed message: " << message << "\n";
}


std::string MessageHandler::MSGToClient()
{
    //std::cout << "MessageHandler::MSGToClient::Queue size : " << app_messages.size() << "\n";
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


void MessageHandler::ClientToMSG(int x, int y)
{
    std::cout << "MessageHandler::ClientToMSG: x = " << x << ", y = " << y << "\n";
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