#pragma once
#include "ConnectionListener.h"
#include "../Game/DefaultLobby.h"
#include "IDQueue.h"

//this class represents the running server instance, managing incoming connections and all lobbies
//this class is a singleton and is not copyable or moveable nor instantiable
class Server : Subscriber<SharedSocket, Server> {
public:
	//allow subscriber interface to call listenHandler
	friend Subscriber<SharedSocket, Server>;

	//starts the server and enables listening in on connections
	void run();

	//shuts down the server, disconnecting all clients and closing all lobbies
	void shutdown();
	
	//returns the static server instance
	static Server& getInstance();

private:

	bool b_run; //flag that tells if server is running
	uint32_t totalConnections; //counts how many clients are connected to this server at this time
	inline static uint32_t maxConnections = 25; //how many connections are allowed at maximum


	//private constructor
	Server();
	//private destructor
	~Server();
	//class is not copyable
	Server(const Server&) = delete;
	//class is not moveable
	Server(Server&&) = delete;

#pragma region Connecting and Communication
	//this function initiates a player instance once the player has connected to the server and their socket has been posted to the queue
	void listenHandler(SharedSocket);

	SharedContext connectContext; //the shared io_context for connecting to the server
	SharedContext commsContext; //the shared io_context for communicating with the server

	asio::io_context::work connectIdleWork; //idle work for the connect context
	asio::io_context::work commsIdleWork; //idle work for the comms context 
	//this could be scalable using a vector and number of connections to determine how many threads to use

	ConnectionListener connectionListener; //listener that waits for incomming connections

	std::thread connectThread; //this thread will execute the connect context and all services that run on it
	std::thread commsThread; //this thread will execute the communications context and all services that run on it
#pragma endregion

	//DefaultLobby defaultLobby; //the default lobby newly connected players are joined to

};

