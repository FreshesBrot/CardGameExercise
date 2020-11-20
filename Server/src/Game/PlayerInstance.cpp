#include "PlayerInstance.h"

PlayerInstance::PlayerInstance(SharedSocket& socket, uint32_t ID) : socket(socket), b_valid(true), uniqueID(ID), lobbyQueue(),
													   information(), listener(socket), sender(socket) {

}

PlayerInstance::PlayerInstance(PlayerInstance&& instance) noexcept : socket(), b_valid(false), uniqueID(0), lobbyQueue(),
																	 information(), listener(socket), sender(socket) {
	*this = std::move(instance);
}

PlayerInstance& PlayerInstance::operator=(PlayerInstance&& instance) noexcept {
	if (this == &instance || !instance.b_valid) return *this;
	
	//handle client instance
	uniqueID = instance.uniqueID;
	instance.uniqueID = 0;
	b_valid = true;
	instance.b_valid = false;

	//handle pointers
	socket = std::move(instance.socket);
	lobbyQueue = std::move(instance.lobbyQueue);
	listener = std::move(listener);
	sender = std::move(sender);

	return *this;
}

void PlayerInstance::closeConnection() {
	if (b_valid) {
		b_valid = false;
		listener.mute();
		(*socket).close();
	}
}

bool PlayerInstance::isValid() const {
	return b_valid;
}

void PlayerInstance::setLobbyQueue(ProtocolQueue& queue) {
	lobbyQueue = queue;
	listener.setQueue(queue);
}

void PlayerInstance::send(ProtocolType protocol) {
	sender.sendRequest(protocol);
}

uint32_t PlayerInstance::getUniqueID() const {
	return uniqueID;
}
