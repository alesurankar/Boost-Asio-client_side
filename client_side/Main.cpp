#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
#include "TCP_Client.h"
#include "App.h"

int main() {

	std::unique_ptr<TCP_Client> client;
	std::atomic<bool> running = true;;
	App app(running);

	boost::asio::io_context io;
	client = std::make_unique<TCP_Client>(io);
	client->Connect();

	std::thread networking([&]() {
		io.run();
		});

	while (running) {
		app.Go();
	}

	io.stop();
	if (networking.joinable()) {
		networking.join();
	}

	return 0;
}