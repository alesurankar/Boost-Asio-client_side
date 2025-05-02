#include "App.h"
#include <iostream>


App::App(std::shared_ptr<MessageHandler> handler)
    :
    msgHandler(handler)
{}


void App::Go()
{
	std::cout << "App::Go:\n";
	PlayerInput();
	DisplayOutput();
}


void App::PlayerInput()
{
    std::cout << "App::PlayerInput:\n";
    std::string input;
    std::getline(std::cin, input);

    if (input == "UP")
    {
        msgHandler->AppToMSG("move_up");
    }
    else if (input == "DWN")
    {
        msgHandler->AppToMSG("move_down");
    }
    else if (input == "LFT")
    {
        msgHandler->AppToMSG("move_left");
    }
    else if (input == "RGT")
    {
        msgHandler->AppToMSG("move_right");
    }

    std::cout << "--------------\n";
}


void App::DisplayOutput()
{
	std::cout << "App::DisplayOutput:\n";
	//std::pair<int, int> pos = msg.MSGToApp();
	//int x = pos.first;
	//int y = pos.second;
	//std::cout << "x: " << x << "\n";
	//std::cout << "y: " << y << "\n";
	std::cout << "--------------\n";
}