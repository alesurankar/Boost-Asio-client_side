#pragma once
#include <string>
#include "MessageHandler.h"

class App
{
public:
	App();
	void Go();
	void TakeInput();
	void DisplayOutput();
private:
	void PlayerInput(const std::string command_in);
	void SendToServer();
	void ReceiveFromServer();
private:
	std::string command;
	MessageHandler msg;
	int x;
	int y;
};