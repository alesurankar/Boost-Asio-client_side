#pragma once
#include <queue>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>

class MessageHandler 
{
public:
    MessageHandler();
    //void ClientToMSG(const std::string& message);
    std::pair<int, int> MSGToApp();
    void AppToMSG(const std::string& message);
    //std::string MSGToClient();
private:
    void MSGToServer(const std::string& message);
    std::pair<int, int> ServerToMSG();
    void ServerCalculations(std::string command);

    // Callback for app to send commands to ChatClient
    std::function<void(const std::string&)> app_to_chatclient_callback;

private:
    std::queue<std::string> app_messages;
    std::queue<std::string> chatclient_messages;
    std::mutex mtx;
    std::condition_variable cv; 
    std::queue<std::pair<int, int>> app_position;
    int x = 100;
    int y = 100;
};