#include "ResponseHandler.h"

ResponseHandler::ResponseHandler(SharedSocket& socket) : 
	socket(socket), b_listen(false), buffer(ResponseHandler::bufferSize), tmpBuffer(ResponseHandler::tmpBufSize), b_valid(true) { }

ResponseHandler::~ResponseHandler() {
	if (b_listen)
		mute();
}

void ResponseHandler::listen() {
	//make sure the socket is open at all (and the handler is valid) before listening in for responses
	if (!(*socket).is_open() || b_valid) {
		throw NoConnectionException("ResponseHandler tried to listen for a response on an invalid handler or closed socket!");
		b_valid = false;
	}

	b_listen = true;
	readHandler();
}

void ResponseHandler::mute() {
	b_listen = false;
	b_valid = false;
}

bool ResponseHandler::isListening() const volatile {
	return b_listen;
}

bool ResponseHandler::isValid() const {
	return b_valid;
}

ResponseHandler::Buffer ResponseHandler::getBuffer() {
	Buffer newBuffer(buffer.begin(), buffer.begin() + curSize);
	curSize = 0;
	return newBuffer;
}

void ResponseHandler::operator()(ResponseHandler&& handler) {
	*this = std::move(handler);
}

void ResponseHandler::readHandler() {
	//if the client is not supposed to listen, break the loop
	if (!b_listen) return;
		

	(*socket).async_read_some(asio::buffer(tmpBuffer.data(), tmpBuffer.size()), [this](asio::error_code err, size_t length) {
		if (err) {
			b_listen = false;
			throw asio::system_error(err);
		}
			
		//copy contents of tmp buffer to position at the last written buffer adress
		memcpy(buffer.data() + length, tmpBuffer.data(), length);
		curSize += length;

		readHandler();
	});

}

ResponseHandler::ResponseHandler(ResponseHandler&& handler) {
	*this = std::move(handler);
}

ResponseHandler& ResponseHandler::operator=(ResponseHandler&& handler) {
	if (this == &handler || !handler.b_valid /*in case the passed handler is not valid, dont bother moving it*/) return *this;
	curSize = 0;
	tmpBuffer.clear();
	//no need to clear the buffer as that one is overwritten anyways
	//make sure to mute this handler before doing anything else
	mute();

		buffer = std::move(handler.buffer);
		curSize = handler.curSize;
		handler.curSize = 0;
		socket = std::move(handler.socket); //this will only keep one reference to the socket alive, destroying the other from the passed handler

		//validate this handler and unvalidate the other
		b_valid = true;
		handler.b_valid = false;
}
