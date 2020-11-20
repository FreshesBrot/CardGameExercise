#pragma once
#include "ConnectionListener.h"
#include "../Game/DefaultLobby.h"

//the server will manage every incomming connection and dispatch protocols to the appropriate queue
//this class is not copyable or moveable
class Server : public Subscriber<SharedSocket, Server> {
public:

	static Server* Instance();

	//this will start the server
	void start();
	//this will shutdown the server
	void shutdown();


private:

	//default constructor for the server
	Server();
	//default destructor
	~Server() { shutdown(); };

	//class is not copyable
	Server(const Server&) = delete;
	//or moveable
	Server(Server&&) = delete;

	//the function that will be executed when a connection from a client has been established. at this point, an open socket is maintaned.
	void listenHandler(SharedSocket socket);

	SharedContext context; //context that listening operates on
	std::thread workerThread; //thread that handles listening on the server

	bool b_isRunning; //flag that tells if the server should run
	std::vector<ConnectionListener> listener; //the connection listener will listen for new clients connecting to the server. if the server needs multiple endpoints, it can create new ones on demand

	inline static Server* instance = nullptr; //capsulated instance of the server
	inline static uint32_t initListeners = 1; //the number of listeners for a server instance. can be scaled up if needed

	DefaultLobby defaultLobby; //the default lobby that is managed by the server. it is likely that there will be several default lobbies at some point

	static uint32_t getAvailableID(); //returns the first available ID
	inline static bool availableIDs[1024]; //contains all available IDs
};