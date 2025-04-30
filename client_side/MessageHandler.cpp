#include "MessageHandler.h"

//void MessageHandler::ClientToMSG(const std::string& message)
//{
//    std::lock_guard<std::mutex> lock(mtx);
//    chatclient_messages.push(message);
//    cv.notify_all();
//}

MessageHandler::MessageHandler()
{}

std::pair<int, int> MessageHandler::MSGToApp()
{
    std::lock_guard<std::mutex> lock(mtx);
    //app_position.push(std::make_pair(x, y));
	return ServerToMSG();
	int z = 0;
}

void MessageHandler::AppToMSG(const std::string& message)
{
    std::unique_lock<std::mutex> lock(mtx);
    //app_messages.pop(message);
	MSGToServer(message);
}

void MessageHandler::ServerCalculations(std::string command)
{
	if (command == "move_up")
	{
		y--;
	}
	if (command == "move_down")
	{
		y++;
	}
	if (command == "move_left")
	{
		x--;
	}
	if (command == "move_right")
	{
		x++;
	}
}

//std::string MessageHandler::MSGToClient()
//{
//    std::unique_lock<std::mutex> lock(mtx);
//    cv.wait(lock, [this] { return !chatclient_messages.empty(); });
//
//    std::string message = chatclient_messages.front();
//    chatclient_messages.pop();
//    return message;
//}

void MessageHandler::MSGToServer(const std::string& message)
{
	ServerCalculations(message);
}

std::pair<int, int> MessageHandler::ServerToMSG()
{
	return std::make_pair(x, y);
}