//entry point for this function
#include <iostream>

#include "src/Server/Server.h"
#include "src/Server/Queues/ProtocolProvider.h"
#include "src/Server/Queues/Subscriber.h"

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

//test class
class TestSub : public Subscriber<int, TestSub> {
public:
	friend Subscriber;

	TestSub() : instance(0), Subscriber(this) { };
	TestSub(const TestSub&) = default;

	
	void setInstance(int i) {
		instance = i;
	}

private:
	int instance;

	void listenHandler(int protocol) {
		COUT << "instance nr #" << instance << " got: " << protocol << NL;
	}

};

int main() {

	std::shared_ptr<ProtocolProvider<int>> queue = std::make_shared<ProtocolProvider<int>>();

	std::vector<TestSub> subs(5);
	try {
		for (int i = 0; i < subs.size(); i++) {
			subs[i].setInstance(i);
			subs[i].subscribe(queue);
			subs[i].listen();
		}

	} catch (Exception& e) {
		COUT << "[Exception]: " << NL;
		COUT << e.what() << NL;
	}

	int in;
	while (1) {
		try {

			//short interactive loop
			COUT << "Please provide input. 0 exits:" << NL;
			std::cin >> in;

			if (in == 0) break;

			for(int i = 0; i < in; i++)
				(*queue).post(in);

		} catch(Exception & e) {
			COUT << "[Exception]: " << NL;
			COUT << e.what() << NL;
		}
	}

	COUT << "Terminating" << NL;

}
#endif