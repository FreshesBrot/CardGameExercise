#include "RequestHandler.h"

//fill in for now
class Protocol;

RequestHandler::RequestHandler(SharedSocket& socket) : socket(socket) {

}

void RequestHandler::sendRequest(void*) {
	if ((*socket).is_open())
		throw NoConnectionException("Client attempted to send Protocol to Server on a closed connection!");

	//this is where sending the response would come in. this could use a queue or something, not sure yet.
	//waiting for the protocol to be defined
}
