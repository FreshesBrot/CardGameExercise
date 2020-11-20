#include "Server.h"

Server* Server::Instance() {
	
	if (!instance)
		instance = new Server();

	return instance;

}

Server::Server() : Subscriber(this), defaultLobby(), context(), b_isRunning(false), listener() {
	//initiate the shared context
	context = std::make_shared<asio::io_context>();
	//give context idle work
	asio::io_context::work idleWork((*context));

	//subscribe the server to the listener queue
	subscribe(ConnectionListener::getQueue());

	//initiate listeners
	for (int i = 0; i <= initListeners; i++)
		listener.push_back(ConnectionListener(context));

}

void Server::start() {
	b_isRunning = true;
	workerThread = std::thread([this]() { (*context).run(); });

	//start all listeners
	for (auto& l : listener)
		l.listen();
}

void Server::shutdown() {
	if (!b_isRunning) return;

	b_isRunning = false;
	for (auto& l : listener)
		l.mute();

	(*context).stop();
	if (workerThread.joinable()) workerThread.join();
}

void Server::listenHandler(SharedSocket socket) {
	uint32_t ID = 0;
	if (!(ID = getAvailableID())) {
		//send the client that no ID is available at the time
		return;
	}
	//make sure to inform the client that the connection was successful
	//(*socket).send(some protocol that contains ID information and what not)
	UniquePlayer newPlayer = std::make_unique<PlayerInstance>(socket, ID);
	defaultLobby.join(std::move(newPlayer));

}

uint32_t Server::getAvailableID() {
	for (int i = 0; i <= 1024; i++) 
		if (availableIDs[i]) {
			availableIDs[i] = false;
			return i + 1;
		}

	return 0;
}
