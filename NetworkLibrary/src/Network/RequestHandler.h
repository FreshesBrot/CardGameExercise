#pragma once
#include <string>

#include "NetworkShorts.h"
#include "../../../Exceptions/src/Exceptions/NoConnectionException.h"


//this class manages sending requests to the server and receiving the answer
//this class is not copyable but moveable
class RequestHandler {
public:

	//initiates an invalid request handler
	RequestHandler();

	//initialize the response handler with a pointer to the open shared socket
	RequestHandler(SharedSocket& socket);
	//move constructor
	RequestHandler(RequestHandler&& handler) noexcept;
	//move assign operator
	RequestHandler& operator=(RequestHandler&& handler) noexcept;

	//destructor - not responsible for destructing the socket!
	~RequestHandler() { };

	//sends the request (in protocol format!) to the server. throws an exception in case the socket is not open
	void sendRequest(ProtocolType protocol);

private:

	bool b_valid; //flag that checks if the sender is valid or not

	SharedSocket socket; //the shared socket that is being accessed
	
};

