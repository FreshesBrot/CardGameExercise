#include "DefaultLobby.h"

void DefaultLobby::join(UniquePlayer&& player) {
	(*player).setLobbyQueue(protocolQueue);
	allPlayers.push_back(std::move(player));
}

void DefaultLobby::closeLobby() {
	allPlayers.clear();
}

DefaultLobby::DefaultLobby() : Subscriber(this), b_open(true), allPlayers(), protocolQueue() {  }

void DefaultLobby::listenHandler(ProtocolType protocol) {
	//all this function really does is send the protocol to each player instance, at least for now
	//later we have to check what kind of protocol has been sent
	//besides, default lobby is not supposed to inform every client
	for (auto& player : allPlayers)
		(*player).send(protocol);
}
