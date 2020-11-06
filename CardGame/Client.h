#pragma once
#include <string>
#include "src/Commands/ParserFactory.h"
#include "ConnectionHandler.h"
#include "RequestHandler.h"

//this class handles everything from starting a local game to connecting to a server
class Client {
public:

	//initialize the client with an io_context
	Client(asio::io_context& context);

	//make sure the client cleanly disconnects from the server
	~Client() { };

	//checks if this client instance is currently connected to a remote game
	bool isConnected() volatile const;

	//connects the client to the server
	void connect();
	//closes the server connection
	void disconnect();
	//sends a string (i.e. command) to the server
	void sendRequest(std::string&& request);



private:
	//sets the command parser for this instance
	void setup();
	bool b_isConnected; //whether this client is connected to a remote game

	CommandParser parser; //this clients parser



	//information that is used to identify this client
	uint32_t lobbyID;
	uint32_t clientID;

	//the client needs an io_context to operate on
	asio::io_context& context;

#ifdef MACHINE_LOCAL //this macros is enabled during debug and will only connect to the local machine
	inline static std::string defaultIP = "127.0.0.1"; //server IP adress
#else						  
	inline static std::string defaultIP = "178.24.54.4"; //insert this machine's global IP here
#endif

	inline static std::string defaultPort = "13"; //default port of the connection listener

};

