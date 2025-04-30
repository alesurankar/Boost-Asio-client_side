#include "MessageHandler.h"

MessageHandler::MessageHandler()
{}

void MessageHandler::ClientToMSG(int x, int y)
{
    std::lock_guard<std::mutex> lock(mtx);
	app_position.push(std::make_pair(x, y));
}

std::pair<int, int> MessageHandler::MSGToApp()
{
    std::lock_guard<std::mutex> lock(mtx);

    auto pos = app_position.front();
    app_position.pop();
    return pos;
}

void MessageHandler::AppToMSG(const std::string& message)
{
    std::unique_lock<std::mutex> lock(mtx);
    app_messages.push(message);
}

std::string MessageHandler::MSGToClient()
{
    std::lock_guard<std::mutex> lock(mtx);
    if (!app_messages.empty())
    {
        std::string msg = app_messages.front();
        app_messages.pop();
        return msg;
    }
    return "";
}