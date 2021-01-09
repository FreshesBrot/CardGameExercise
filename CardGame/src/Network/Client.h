#pragma once
#include <string>
#include "../../../Commands/CommandCommon.h"
#include "ConnectionHandler.h"
#include "../../../Exceptions/src/Exceptions/InvalidHandlerAccessException.h"

//this class handles everything from starting a local game to connecting to a server
class Client {
public:

	//initialize the client with an io_context
	Client();

	//make sure the client cleanly disconnects from the server
	~Client() { disconnect(); };

	//checks if this client instance is currently connected to a remote game
	bool isConnected() volatile const;

	//connects the client to the server and intializes the shared socket for this client instance. 
	//Throws an exception in case the connection was unsuccesfull or is destroyed.
	void connect();
	//closes the server connection
	void disconnect();
	//sends a string (i.e. command) to the server
	void sendRequest(ProtocolType request);

	//returns the response handler managed by this client instance. throws an exception if the handler is in an invalid state
	RequestListener& getHandler();

private:
	//sets the command parser for this client instance
	void parserSetup();
	//intializes the IO context for this client instance, giving it idle work
	void contextSetup();
	
	bool b_isConnected; //whether this client is connected to a server

	CommandParser parser; //this clients parser

	SharedSocket sharedSocket; //this clients connection socket that is shared between the request and response handler
	uint32_t clientID; //information that is used to identify this client on the server side
	SharedContext context; //the client needs an io_context to operate on

	RequestListener requestListener; //some classes need to access this handler!
	RequestHandler requestHandler; //handler that manages sending requests to the server

	std::thread commsThread; //the thread where the io_context will run on, managed by this class

#ifdef MACHINE_LOCAL //this macros is enabled during debug and will only connect to the local machine
	inline static std::string defaultIP = "127.0.0.1"; //server IP adress
#else						  
	inline static std::string defaultIP = "178.240.lol.xdd"; //insert this machine's global IP here
#endif

	inline static std::string defaultPort = "13"; //default port of the connection listener

};

