#include "RequestHandler.h"

RequestHandler::RequestHandler() : b_valid(false), socket() {
}

RequestHandler::RequestHandler(SharedSocket& socket) : socket(socket), b_valid(true) {

}

RequestHandler::RequestHandler(RequestHandler&& handler) noexcept : socket() {
	*this = std::move(handler);
}

RequestHandler& RequestHandler::operator=(RequestHandler&& handler) noexcept {
	if (this == &handler || !handler.b_valid) return *this;
	
	handler.b_valid = false;
	b_valid = true;
	socket = std::move(handler.socket);

	return *this;
}

void RequestHandler::sendRequest(ProtocolType protocol) {
	if ((*socket).is_open())
		throw NoConnectionException("Client attempted to send Protocol to Server on a closed connection!");

	//this is where sending the response would come in. use send_async so its not blocking.
	//waiting for the protocol to be defined
}
