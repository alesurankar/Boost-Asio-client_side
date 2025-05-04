#pragma once
#include <queue>
#include <string>
#include <mutex>

class MessageHandler
{
public:
    MessageHandler();
    void AppToMSG(const std::string& message);
    std::string MSGToClient();
//    void ClientToMSG(int x, int y);
//    std::pair<int, int> MSGToApp();
private:
    std::mutex mtx;
    std::string msg = "";
    std::queue<std::string> app_messages;
//    std::queue<std::string> client_messages;
//    std::queue<std::pair<int, int>> app_position;
};