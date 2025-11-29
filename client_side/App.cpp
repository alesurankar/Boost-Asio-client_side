#include "App.h"
#include <iostream>

App::App(std::atomic<bool>& running_in)
	:
	running(running_in)
{
}

void App::Go()
{
	std::cout << "App::Go:\n";

	running = false;

	std::cout << "--------------\n\n";
}
