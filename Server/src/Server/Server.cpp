#include "Server.h"

Server::Server() : 
		Subscriber(this), b_run(false), totalConnections(0),
		connectContext(std::make_shared<asio::io_context>()), connectIdleWork((*connectContext)), connectThread(),
		commsContext(std::make_shared<asio::io_context>()), commsIdleWork((*commsContext)), commsThread(),
		connectionListener(connectContext, commsContext) {

	//subscribe the server to the connectionlistener queue
	subscribe(ConnectionListener::getQueue());
}

Server::~Server() { shutdown(); /*make sure server shuts down cleanly when it gets destroyed*/ }

void Server::run() {
	if (b_run) return;

	//start connect context on connectThread
	connectThread = std::thread([this]() {(*connectContext).run(); });
	//start comms context on commsThread
	commsThread = std::thread([this]() {(*commsContext).run(); });
	//listen in on the subscribed queue
	listen();
	//start connection listener
	connectionListener.listen();
	//clear the IDqueue and reinitiliaze all 

	b_run = true;
}

void Server::shutdown() {
	if (!b_run) return;

	b_run = false;
	//close all connections and block incomming connections
	connectionListener.mute();
	//stop listening on the subscribed queue
	mute();
	//close all lobbies, disconnecting all clients
	/*..*/
	//join worker threads
	if (connectThread.joinable()) connectThread.join();
	if (commsThread.joinable()) commsThread.join();
}

void Server::listenHandler(SharedSocket socket) {
	//fetch an available ID from the IDQueue
	uint32_t uniqueID = 0;
	//create player instance
	SharedPlayer player = std::make_shared<PlayerInstance>(socket, uniqueID);
	//join new player to default lobby
	//defaultLobby.join(player);
}

Server& Server::getInstance() {
	static Server svr;
	return svr;
}