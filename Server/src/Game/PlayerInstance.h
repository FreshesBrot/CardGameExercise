#pragma once
#include "../../../NetworkLibrary/src/Network/NetworkDefs.h"

class PlayerInstance;

typedef std::unique_ptr<PlayerInstance> UniquePlayer;

//this class represents a single connected client
//this class is not copyable but moveable
class PlayerInstance {
public:


	//constructor that initializes the player instance with its associated socket
	PlayerInstance(SharedSocket& socket, uint32_t ID);

	~PlayerInstance() { closeConnection();  };
	//move constructs the player instance from another player
	PlayerInstance(PlayerInstance&& instance) noexcept;
	//move assignment operator to move instances around
	PlayerInstance& operator=(PlayerInstance&& instance) noexcept;

	//this will close the connection, ultimately making the instance dead. this will also mark the client ID as free again
	void closeConnection();

	//returns if this client is valid or not
	bool isValid() const;

	//this function will set what lobby queue the client instance should post to
	void setLobbyQueue(ProtocolQueue& queue);

	//sends a protocol to the client 
	void send(ProtocolType protocol);

	uint32_t getUniqueID() const;

private:

	//this class is not copyable
	PlayerInstance(const PlayerInstance&) = delete;

	bool b_valid; //flag that checks if the client is valid or not
	
	SharedSocket socket; //the socket that is used to communicate to the connected client
	uint32_t uniqueID; //this clients unique connection ID. 0 is not a valid ID
	
	RequestListener listener; //the listener that listens in on incoming requests or protocols. posts protocols to the lobby queue when something arrives
	RequestHandler sender; //the handler that sends data back to the client

	ProtocolQueue lobbyQueue; // the lobby queue that the player instance will post to

	ProtocolType information; //this variable has to hold the protocol information
};