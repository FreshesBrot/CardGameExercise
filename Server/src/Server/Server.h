#pragma once
#include "../../../NetworkLibrary/src/Network/NetworkDefs.h"

//this class represents the running server instance, managing incoming connections and all lobbies
//this class is a singleton and is not copyable or moveable nor instantiable
class Server {
public:


	//starts the server and enables listening in on connections
	void run();

	//shuts down the server, disconnecting all clients and closing all lobbies
	void shutdown();
	
	//returns the static server instance
	static Server& getInstance() {
		static Server srv;
		return srv;
	}

private:

	bool b_run; //flag that tells if server is running

	//private constructor
	Server();
	//private destructor
	~Server();
	//class is not copyable
	Server(const Server&) = delete;
	//class is not moveable
	Server(Server&&) = delete;

};

