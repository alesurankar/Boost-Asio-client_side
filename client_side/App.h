#pragma once
#include "MessageHandler.h"
#include <string>

class App
{
public:
	App(std::atomic<bool>& runFlag, std::shared_ptr<MessageHandler> msgHandler_in);
	void Go();
private:
	void PlayerInput();
	void outputLoop();
	void DisplayOutput();
private:
	std::shared_ptr<MessageHandler> msgHandler;
	std::thread outputThread; 
	std::atomic<bool>& running;
};