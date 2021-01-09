#pragma once
#include "PlayerInstance.h"

//this class represents a default lobby and is a base class for the game lobby.
//this class is not copayble but moveable
class DefaultLobby {
public:

	//constructs a lobby with room for players to join
	DefaultLobby();
	//move constructor that will move all players in this lobby to the new one, deleting this lobby in the process
	DefaultLobby(DefaultLobby&&);

	//lets a player join this lobby instance
	void join(SharedPlayer&);

	//lets a player leave this instance (though leaving default lobby would just disconnect)
	void leave(SharedPlayer&);

private:

	//this class is not copyable
	DefaultLobby(const DefaultLobby&) = delete;
};

