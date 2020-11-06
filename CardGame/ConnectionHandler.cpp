#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler(asio::io_context& context) : 
		tmpBuffer(tmpBufferSize), buffer(bufferSize), context(context), connectSocket(context), curSize(0), b_receiving(false) { }

ConnectionHandler::~ConnectionHandler() { }

uint32_t ConnectionHandler::connect(std::string& IP, std::string& port) {
	TCP::resolver resolver(context);
	
	asio::error_code err;

	//(async)connect to the server
	asio::connect(connectSocket, resolver.resolve(IP, port));

	b_receiving = true;
	readHandler();

	return 0;
}

bool ConnectionHandler::isReceiving() const volatile {
	return b_receiving;
}

std::vector<byte_t>&& ConnectionHandler::getBuffer() {
	curSize = 0;
	return std::move(buffer);
}

size_t ConnectionHandler::getReadSize() const {
	return curSize;
}

void ConnectionHandler::readHandler() {

	//everything thats being done here is essentially writing the data into the buffer and then exiting
	connectSocket.async_read_some(asio::buffer(tmpBuffer.data(), tmpBuffer.size()), 
		[&](asio::error_code err, size_t length) {
			if (err) {
				b_receiving = false;
				return;
			}

			//move contents of tmpBuffer into the actual buffer
			memcpy(buffer.data() + curSize, tmpBuffer.data(), length);
			curSize += length;

			readHandler();
		}
		);
}

