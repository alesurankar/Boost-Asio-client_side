#include "App.h"
#include <iostream>

App::App()
{}

void App::Run()
{
	TakeInput();
	DisplayOutput();
}

void App::TakeInput()
{
	std::cout << "TakeInput: ";
	std::string message;
	std::getline(std::cin, message);
	PlayerInput(message);
	std::cout << "--------------\n";
}

void App::DisplayOutput()
{
	std::cout << "DisplayOutput:\n";
	ReceiveFromServer();
	std::cout << "x: " << x << "\n";
	std::cout << "y: " << y << "\n";
	std::cout << "--------------\n";
}


void App::PlayerInput(const std::string command_in)
{
	std::cout << "PlayerInput:\n";
	if (command_in == "UP")
	{
		command = "move_up";
		SendToServer();
	}
	if (command_in == "DWN")
	{
		command = "move_down";
		SendToServer();
	}
	if (command_in == "LFT")
	{
		command = "move_left";
		SendToServer();
	}
	if (command_in == "RGT")
	{
		command = "move_right";
		SendToServer();
	}
	std::cout << "--------------\n";
}

void App::SendToServer()
{
	std::cout << "SendToServer:\n";
	msg.AppToMSG(command);
	std::cout << "--------------\n";
}

void App::ReceiveFromServer()
{
	std::cout << "ReceiveFromServer:\n"; 
	std::pair<int, int> pos = msg.MSGToApp();
	x = pos.first;
	y = pos.second;

	std::cout << "--------------\n";
}