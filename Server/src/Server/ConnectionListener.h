#pragma once
#include "../../../NetworkLibrary/NetworkCommon.h"


//this class represents the connection interface between the client and the server
class ConnectionListener {
public:

	typedef std::shared_ptr<ObjectProvider<SharedSocket>> ConnectionQueue;

	//constructor that initializes all necessary components to listen for connections
	ConnectionListener(SharedContext& connectContext, SharedContext& commsContext);

	//starts listening for connections
	void listen();

	//mutes the connection listener and blocks incomming connections
	void mute();

	//returns the connection queue for the ConnectionListener class
	static ConnectionQueue& getQueue(); 

private:

	bool b_listen; //flag that tells if the listener should be listening for incomming connections

	SharedContext connectContext; //shared context to run accept service on
	TCP::acceptor acceptor; //an acceptor endpoint to instantiate connections

	SharedContext commsContext; //shared context to run socket communications on

	inline static std::string IP = "192.168.0.2"; //the local ip of the machine
	inline static uint16_t PORT = 13; //the port that accepts incomming connections

	inline static ConnectionQueue connections = std::make_shared<ObjectProvider<SharedSocket>>(); //queue that will have all incomming connections


	//this function will handle incomming connections 
	void handleConnect();

};

