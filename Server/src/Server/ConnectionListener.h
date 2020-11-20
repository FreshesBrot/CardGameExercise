#pragma once

#include <string>
#include <memory>
#include "../../../NetworkLibrary/src/Network/NetworkDefs.h"


//this class will listen in on incomming connections
//this class is not copyable and not moveable
class ConnectionListener {
public:

	typedef std::shared_ptr<ObjectProvider<SharedSocket>> ConnectQueue;

	//default constructor of the listener that takes an io context ref to operate on
	ConnectionListener(SharedContext& context);
	//deconstructor makes sure listening is muted
	~ConnectionListener() { mute();  };
	//copy constructor for the listener class. copying will automatically start listening
	ConnectionListener(const ConnectionListener& listener);
	

	//make the connection listener listen for incomming connections
	void listen();
	//mute the connection listener 
	void mute();

	//returns the static queue all connection listeners will operate on
	static ConnectQueue& getQueue();

private:
	
	inline static std::string ip = "192.168.0.2"; //the ip the listener will listen on
	inline static std::string port = "13"; //the port the listener will listen on

	bool b_listen; //flag that tells the listener if its accepting connections or not

	SharedContext context;	//internal context the connection listener will operate on
	TCP::acceptor acceptor;		//internal endpoint a client can connect to
	
	//this function will handle incomming connections
	void handleAccept(); 


	static ConnectQueue connectionQueue; //this queue keeps track of all posted incomming connections
};

