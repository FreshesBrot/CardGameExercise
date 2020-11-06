#include "Client.h"

Client::Client(asio::io_context& context) : context(context) {
	setup();
}


bool Client::isConnected() const volatile {
	return b_isConnected;
}

void Client::connect() {
	ConnectionHandler connectionHandler(context);
	connectionHandler.connect(defaultIP, defaultPort);
	while (connectionHandler.isReceiving());

	size_t readSize = connectionHandler.getReadSize();
	std::vector<byte_t> buf = connectionHandler.getBuffer();

	std::cout.write(buf.data(), readSize);
}

void Client::setup() {
	//CREATE COMMAND PARSER HERE
}