#include "App.h"
#include <iostream>


App::App(std::shared_ptr<MessageHandler> msgHandler_in)
    :
    msgHandler(msgHandler_in)
{}


void App::Go()
{
    std::cout << "App::Go:\n";
    PlayerInput(); //1. AppClient(input)
    //DisplayOutput(); //11. AppClient(displayOutput)
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


//void App::DisplayOutput() //11. AppClient(displayOutput)
//{
//    std::cout << "App::DisplayOutput: //11. AppClient(displayOutput)\n";
//    std::pair<int, int> pos = msgHandler->MSGToApp(); //10. MSGClient(middleman)
//    int x = pos.first;
//    int y = pos.second;
//    std::cout << "x: " << x << "\n";
//    std::cout << "y: " << y << "\n";
//    std::cout << "--------------\n";
//}