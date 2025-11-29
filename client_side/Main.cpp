#include <iostream>
#include <atomic>
#include <memory>
#include "TCP_Client.h"
#include "App.h"

int main() {

	std::unique_ptr<TCP_Client> client;
	std::atomic<bool> running = true;;
	App app(running);

	while (running) {
		app.Go();
	}

	return 0;
}