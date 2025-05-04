#include "MessageHandler.h"
#include <iostream>


MessageHandler::MessageHandler()
{}


void MessageHandler::AppToMSG(const std::string& message)  //2. MSGClient(middleman)
{
    std::lock_guard<std::mutex> lock(mtx1);
    std::cout << "Step 2: MainThread::MessageHandler::AppToMSG: " << message << "\n";
    app_messages.push(message);
    std::cout << "Pushed message: " << message << "\n";
    std::cout << "Step2--------------\n";
}


std::string MessageHandler::MSGToClient()  //3. Client(TCP)
{
    {
        std::lock_guard<std::mutex> lock(mtx2);
        if (!app_messages.empty())
        {
            std::cout << "Step 3: NetworkingThread::MessageHandler::MSGToClient: " << msg << "\n";
            msg = app_messages.front();
            app_messages.pop();
            std::cout << "Popped message: " << msg << "\n";
            std::cout << "Step3--------------\n";
        }
        else
        {
            msg = "";
        }
    }
    return msg; //3. Client(TCP)
}


//void MessageHandler::ClientToMSG(int x, int y) //10. MSGClient(middleman)
//{
//    std::cout << "MessageHandler::ClientToMSG: x = " << x << ", y = " << y << "//10. MSGClient(middleman)\n";
//    std::lock_guard<std::mutex> lock(mtx);
//    app_position.push(std::make_pair(x, y));
//}
//
//
//std::pair<int, int> MessageHandler::MSGToApp()
//{
//    std::cout << "MessageHandler:MSGToApp:\n";
//    std::lock_guard<std::mutex> lock(mtx);
//
//    auto pos = app_position.front();
//    app_position.pop();
//    return pos;
//}