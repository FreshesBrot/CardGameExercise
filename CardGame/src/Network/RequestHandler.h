#pragma once
#include <string>
#include <memory>
#include <asio-1.18.0/include/asio.hpp>

#include "../Exceptions/NoConnectionException.h"

using TCP = asio::ip::tcp;
typedef std::shared_ptr<TCP::socket> SharedSocket;


//this class manages sending requests to the server and receiving the answer
class RequestHandler {
public:

	//initialize the response handler with a pointer to the open shared socket
	RequestHandler(SharedSocket& socket);

	//destructor - not responsible for destructing the socket!
	~RequestHandler() { };

	//sends the request (in protocol format!) to the server. throws an exception in case the socket is not open
	void sendRequest(void* protocol);

private:

	//the shared socket that is being accessed
	SharedSocket socket;

};

