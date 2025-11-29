#pragma once
#include <atomic>

class App 
{
public:
	App(std::atomic<bool>& running_in);
	void Go();
private:
	std::atomic<bool>& running;
};