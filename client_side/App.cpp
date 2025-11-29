#include "App.h"

App::App(std::atomic<bool>& running_in)
	:
	running(running_in)
{
}

void App::Go()
{
	running = false;
}
