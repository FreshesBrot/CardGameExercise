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
		ConnectionHandler connecter(context);
		connecter.connect(defaultIP, defaultPort);

		sharedSocket = connecter.getSocketInstance();

		//set socket option keep connection alive and initialize the handler to listen
		(*sharedSocket).set_option(asio::socket_base::keep_alive(true));
		
		responseHandler(ResponseHandler(sharedSocket));
		responseHandler.listen();
		
		//if no exception was thrown, the client should be connected
		b_isConnected = true;
}

void Client::disconnect() {
	responseHandler.mute();
	(*sharedSocket).close();
	b_isConnected = false;

	context.stop();
	if (commsThread.joinable()) commsThread.join();
}

ResponseHandler& Client::getHandler() {
	if (!responseHandler.isValid())
		throw InvalidHandlerAccessException("An object tried to retrieve reference to an invalid ResponseHandler!");

	return responseHandler;
}

void Client::parserSetup() {
	//CREATE COMMAND PARSER HERE
}

void Client::contextSetup() {
	//give the context idle work so it doesnt exit
	asio::io_context::work idleWork(context);
	
	//run the context with idle work. this will still take new async operations
	commsThread = std::thread([this]() {
		context.run();
	});
}