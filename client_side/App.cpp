#include "App.h"
#include <iostream>


App::App(std::atomic<bool>& runFlag, std::shared_ptr<MessageHandler> msgHandler_in)
    :
    msgHandler(msgHandler_in),
    running(runFlag)
{
    outputThread = std::thread(&App::outputLoop, this);
}

App::~App()
{
    if (outputThread.joinable())
    {
        outputThread.join();
    }
}

void App::Go()
{
    std::cout << "App::Go:\n";
    PlayerInput(); //1. AppClient(input)
}

void App::outputLoop()
{
    while (running) 
    {
        DisplayOutput(); //11. AppClient(displayOutput)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


void App::PlayerInput() //1. AppClient(input)
{
    std::cout << "MainThread::App::PlayerInput:\n\n";
    std::string input;
    std::getline(std::cin, input);

    if (input == "UP")
    {
        std::cout << "Step 1: MainThread::App::PlayerInput: "<< input << "\n";
        msgHandler->AppToMSG("move_up"); //2. MSGClient(middleman)
    }
    else if (input == "DWN")
    {
        std::cout << "Step 1: MainThread::App::PlayerInput: " << input << "\n";
        msgHandler->AppToMSG("move_down"); //2. MSGClient(middleman)
    }
    else if (input == "LFT")
    {
        std::cout << "Step 1: MainThread::App::PlayerInput: " << input << "\n";
        msgHandler->AppToMSG("move_left"); //2. MSGClient(middleman)
    }
    else if (input == "RGT")
    {
        std::cout << "Step 1: MainThread::App::PlayerInput: " << input << "\n";
        msgHandler->AppToMSG("move_right"); //2. MSGClient(middleman)
    }

    std::cout << "Step1--------------\n\n";
}


void App::DisplayOutput() //15. AppClient(displayOutput)
{
    //std::cout << "Step 15, outputThread::App::DisplayOutput:\n\n";
    auto optPos = msgHandler->MSGToApp(); 
    if (optPos)
    {
        std::pair<int, int> pos = *optPos;
        int x = pos.first;
        int y = pos.second;
        std::cout << "Step 15-------------Last Step Done\n";
        std::cout << "x: " << x << "\n";
        std::cout << "y: " << y << "\n";
        std::cout << "OUTPUT--------------Last Step Done\n\n";
    }
}