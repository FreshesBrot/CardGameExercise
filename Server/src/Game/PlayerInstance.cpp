#include "PlayerInstance.h"

PlayerInstance::PlayerInstance(SharedSocket& socket, uint32_t uniqueID) : 
	ID(uniqueID), reqHandler(socket), reqListener(socket) {

}

const uint32_t PlayerInstance::getPlayerID() {
	return ID;
}
