#pragma once
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

class MessageHandler 
{
public:
    MessageHandler();
    void AppToMSG(const std::string& message);
    std::string MSGToClient();
    void ClientToMSG(int x, int y);
    std::pair<int, int> MSGToApp();
private:
    std::queue<std::string> app_messages;
    std::queue<std::string> client_messages;
    std::mutex mtx;
    std::queue<std::pair<int, int>> app_position;
};