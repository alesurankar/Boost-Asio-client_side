#include "MessageHandler.h"
#include <iostream>


MessageHandler::MessageHandler()
{}


void MessageHandler::AppToMSG(const std::string& message)  //2. MSGClient(middleman)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Step 2: MainThread::MessageHandler::AppToMSG: " << message << "\n";
    app_messages.push(message);
    std::cout << "Pushed message: " << message << "\n";
    std::cout << "Step2--------------\n";
}


std::string MessageHandler::MSGToClient()  //3. Client(TCP)
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!app_messages.empty())
        {
            std::cout << "Step 3: NetworkingThread::MessageHandler::MSGToClient: " << msg << "\n";
            msg = app_messages.front() + "\n";
            app_messages.pop();
            std::cout << "Popped message: " << msg;
            std::cout << "Step3--------------\n";
        }
        else
        {
            msg = "";
        }
    }
    return msg; //3. Client(TCP)
}


void MessageHandler::ClientToMSG(int x, int y) //13. MSGClient(middleman)
{
    std::cout << "Step 13, MessageHandler::ClientToMSG: x = " << x << ", y = " << y << "\n";
    std::lock_guard<std::mutex> lock(mtx);
    app_position.push(std::make_pair(x, y));
    std::cout << "Step13--------------\n";
}


std::optional<std::pair<int, int>> MessageHandler::MSGToApp()
{
    std::lock_guard<std::mutex> lock(mtx);
    if (!app_position.empty())
    {
        std::cout << "Step 14, MessageHandler:MSGToApp:\n";
        std::pair<int, int> pos = app_position.front();
        app_position.pop();
        int x = pos.first;
        int y = pos.second; 
        std::cout << "Popped position and extracted value: " << "x = " << x << ", y = " << y << "\n";
        std::cout << "Step14--------------\n";
        return pos;
    }
    else
    {
        std::cout << "[Output] No data to display.\n";
        return std::nullopt;
    }
}