#pragma once
#include "MessageHandler.h"
#include <string>

class App
{
public:
	App(std::atomic<bool>& runFlag, std::shared_ptr<MessageHandler> msgHandler_in);
	~App();
	void Go();
private:
	void PlayerInput();
	void OutputLoop();
	void DisplayOutput();
private:
	std::shared_ptr<MessageHandler> msgHandler;
	std::thread OutputThread; 
	std::atomic<bool>& running;
};