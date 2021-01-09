#include "RequestListener.h"

RequestListener::RequestListener(SharedSocket& socket) : 
	socket(socket), b_listen(false), buffer(RequestListener::bufferSize), tmpBuffer(RequestListener::tmpBufSize), b_valid(true) { }

RequestListener::RequestListener(RequestListener&& listener) noexcept {
	*this = std::move(listener);
}

RequestListener& RequestListener::operator=(RequestListener&& listener) noexcept {
	if (this == &listener || !listener.b_valid /*in case the passed handler is not valid, dont bother moving it*/) return *this;
	curSize = 0;
	tmpBuffer.clear();
	//no need to clear the buffer as that one is overwritten anyways
	//make sure to mute this handler before doing anything else
	mute();

	buffer = std::move(listener.buffer);
	curSize = listener.curSize;
	listener.curSize = 0;
	socket = std::move(listener.socket); //this will only keep one reference to the socket alive, destroying the other from the passed handler
	queue = std::move(listener.queue);


	//validate this handler and unvalidate the other
	b_valid = true;
	listener.b_valid = false;

	return *this;
}

RequestListener::~RequestListener() {
	if (b_listen)
		mute();
};

void RequestListener::listen() {
	//make sure the socket is open at all (and the handler is valid) before listening in for responses
	if (!(*socket).is_open() || b_valid) {
		throw NoConnectionException("ResponseHandler tried to listen for a response on an invalid handler or closed socket!");
		b_valid = false;
	}

	if (!b_listen) {
		b_listen = true;
		listenHandler();
	}	
}

void RequestListener::mute() {
	b_listen = false;
	b_valid = false;
}

void RequestListener::setQueue(ProtocolQueue queue) {
	this->queue = queue;
}

bool RequestListener::isListening() const volatile {
	return b_listen;
}

bool RequestListener::isValid() const {
	return b_valid;
}


void RequestListener::listenHandler() {
	//if the client is not supposed to listen, break the loop
	if (!b_listen) return;
		
	(*socket).async_read_some(asio::buffer(tmpBuffer.data(), tmpBuffer.size()), [this](asio::error_code err, size_t length) {
		//if the client is not supposed to listen, break the loop
		if (!b_listen) return;

		if (err) {
			b_listen = false;
			throw asio::system_error(err);
		}

		//if a protocol arriving procs this function, its guaranteed that its the first bytes coming in
		curSize = 0;
		buffer.clear();
		//expectedSize = somethingsomething protocol;

		memcpy(buffer.data() + curSize, tmpBuffer.data(), length);
		curSize += length;

		//call subroutine function that will handle reading protocol until its done
		b_receiving = true;
		handleProtocol();
		//block until handleProtocol is actually done
		while (!b_receiving);

		//once handleProtocol is done, this means that the entire protocol has arrived and can now be sent to the translation unit and posted to the queue
		(*queue) += 0;

		//then, get back to waiting for new requests
		listenHandler();
	});

}

void RequestListener::handleProtocol() {

	(*socket).async_read_some(asio::buffer(tmpBuffer.data(), tmpBuffer.size()), [this](asio::error_code err, size_t length) {
		if (err) {
			b_listen = false;
			throw asio::system_error(err);
		}

		//copy contents of tmp buffer to position at the last written buffer adress
		memcpy(buffer.data() + curSize, tmpBuffer.data(), length);
		curSize += length;

		//read as long as there are bytes expected
		if (curSize != expectedSize)
			handleProtocol();
		else b_receiving = false;
	});

}
