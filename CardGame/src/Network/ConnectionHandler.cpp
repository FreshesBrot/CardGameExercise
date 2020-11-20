#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler(SharedContext& context) : context(context) { 
	connectSocket = std::make_shared<TCP::socket>((*context));
}

void ConnectionHandler::connect(std::string& IP, std::string& port) {
	TCP::resolver resolver((*context));
	
	asio::error_code err;

	//connect to the server and check errors
	asio::connect(*connectSocket, resolver.resolve(IP, port));
	if (err)
		throw asio::system_error(err);
}

SharedSocket ConnectionHandler::getSocketInstance() {
	if (!(*connectSocket).is_open())
		throw NoConnectionException("Attempted to retrieve socket from an unestablished connection from the ConnectionHandler!");

	return connectSocket;
}


