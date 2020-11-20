#pragma once
#include <string>
#include "../../../NetworkLibrary/src/Network/NetworkDefs.h"
#include "../../../Exceptions/src/Exceptions/NoConnectionException.h"


//this class will manage connecting to the remote server for the first time and initiating an open socket to the server
//this class is not copyable or moveable
class ConnectionHandler {
public:

	//will start the connection handler and wait for it to connect
	ConnectionHandler(SharedContext& context);

	//will stop the connection handler
	~ConnectionHandler() { };


	//attempts to connect to the server. will throw an exception if an error occured.
	void connect(std::string& IP, std::string& port);

	//returns the connection handlers socket instance.
	SharedSocket getSocketInstance();

private:

	SharedContext context; //the context this class will operate on
	SharedSocket connectSocket; //the shared socket that will handle the connection


	ConnectionHandler(const ConnectionHandler&) = delete;
	ConnectionHandler(ConnectionHandler&&) = delete;
};