#pragma once

#include "../../../NetworkLibrary/NetworkCommon.h"

class PlayerInstance;
//type that represents a unique player that can be shared across resources
typedef std::shared_ptr<PlayerInstance> SharedPlayer;

//this class represents a connected player instance with a unique ID and tcp-socket
//this class is not copyable or moveable
class PlayerInstance {
public:

	//constructor that takes a socket that connects to the player this instance is representing, and their unique id assigned from the server
	PlayerInstance(SharedSocket& socket, uint32_t uniqueID);

	//returns this player's 
	const uint32_t getPlayerID();

private:
	const uint32_t ID; //unique ID of this player instance
	
	//this class is not copyable
	PlayerInstance(const PlayerInstance&) = delete;
	//this class is not moveable
	PlayerInstance(PlayerInstance&&) = delete;

	RequestHandler reqHandler; //interface to communicate to the client
	RequestListener reqListener; //interface to recieve from the client

};

