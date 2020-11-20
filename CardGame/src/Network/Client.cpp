#include "Client.h"

Client::Client() : context() {
	//initialize the command parser
	parserSetup();
	//initiliaze context
	contextSetup();
}


bool Client::isConnected() const volatile {
	return b_isConnected;
}

void Client::connect() {
		//establish a connection to the server
		ConnectionHandler connector(context);
		connector.connect(defaultIP, defaultPort);

		sharedSocket = connector.getSocketInstance();

		//set socket option keep connection alive and initialize the handler to listen
		(*sharedSocket).set_option(asio::socket_base::keep_alive(true));
		
		requestHandler = RequestHandler(sharedSocket);
		responseHandler = RequestListener(sharedSocket);
		responseHandler.listen();

		//if no exception was thrown, the client should be connected
		b_isConnected = true;
}

void Client::disconnect() {
	if (!b_isConnected) return;
	
	b_isConnected = false;

	responseHandler.mute();
	(*sharedSocket).close();
	b_isConnected = false;

	(*context).stop();
	if (commsThread.joinable()) commsThread.join();
}

void Client::sendRequest(ProtocolType request) {

}

RequestListener& Client::getHandler() {
	if (!responseHandler.isValid())
		throw InvalidHandlerAccessException("An object tried to retrieve reference to an invalid ResponseHandler!");

	return responseHandler;
}

void Client::parserSetup() {
	//CREATE COMMAND PARSER HERE
}

void Client::contextSetup() {
	//give the context idle work so it doesnt exit
	asio::io_context::work idleWork((*context));
	
	//run the context with idle work. this will still take new async operations
	commsThread = std::thread([this]() { (*context).run(); });
}