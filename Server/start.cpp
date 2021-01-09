//entry point for this function
#include <iostream>

#include "src/Server/Server.h"

#define COUT std::cout
#define NL std::endl

#define TESTING

#ifndef TESTING
using TCP = asio::ip::tcp;

bool b_run = true;

void handleAccept(TCP::acceptor& acceptor) {

	acceptor.async_accept(
		[&](asio::error_code err, TCP::socket socket) {
			if (err) {
				b_run = false;
			};

			std::cout << "established Connection!" << std::endl;

			char buf[] = { '1','2','3' };

			socket.send(asio::buffer(buf, 3));
			socket.close();

			std::cout << "Sent to and closed socket." << std::endl;

			handleAccept(acceptor);
	});
}

int main() {
	try {

		asio::io_context context;
		asio::io_context::work idleWork(context);
		std::thread worker = std::thread([&]() { context.run(); });

		TCP::acceptor acceptor(context, TCP::endpoint(TCP::v4(), 13));

		TCP::socket socket(context);

		std::cout << "Waiting for connections..." << std::endl;
		handleAccept(acceptor);
		
		while (b_run);

		context.stop();
		if (worker.joinable()) worker.join();

		std::cout << "Server terminated";

	} catch (std::exception& e) {
		std::cout << "Error occured:" << std::endl;
		std::cout << e.what();
	}

}
#else



int main() {
	
	SharedContext context(std::make_shared<asio::io_context>());
	TCP::acceptor((*context), TCP::v4());

}
#endif