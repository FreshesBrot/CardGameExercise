#pragma once
#include <vector>
#include "PlayerInstance.h"



//this class represents a simple lobby - a collection of connected clients. no games can be run here.
class DefaultLobby : Subscriber<ProtocolType, DefaultLobby> {
public:
	friend Subscriber;


	//construct the default lobby
	DefaultLobby();

	//when a default lobby gets destroyed, the server shut down
	//this destruction will close all connections on this default lobby!
	~DefaultLobby() {};


	//this lets the player join this lobby
	void join(UniquePlayer&& player);

protected:
	//this will close the lobby, closing all connections.
	virtual void closeLobby();

private:

	//flag that checks if this lobby is open
	bool b_open;

	//the function that handles incoming protocols
	void listenHandler(ProtocolType protocol);

	std::list<UniquePlayer> allPlayers; //all players that are in this queue
	ProtocolQueue protocolQueue; //the protocol queue
	
};

