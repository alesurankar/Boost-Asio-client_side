#include <atomic>
#include <memory>
#include <thread>
#include "TCP_Client.h"
#include "App.h"

int main() {

	std::shared_ptr<TCP_Client> client;
	std::atomic<bool> running = true;;
	App app(running);

	boost::asio::io_context io;
	std::string address = "127.0.0.1";
	uint16_t port = 1234;
	std::string username = "majmun";

	client = std::make_shared<TCP_Client>(io, address, port, username);
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