#pragma once
#include <string>
#include "MessageHandler.h"

class App
{
public:
	App(std::shared_ptr<MessageHandler> msgHandler_in);
	void Go();
	void PlayerInput();
//	void DisplayOutput();
private:

	std::shared_ptr<MessageHandler> msgHandler;
};