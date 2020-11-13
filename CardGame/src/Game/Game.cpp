#include "Game.h"

Game::Game(Deck&& deck, Players players) : 
										playingDeck(std::move(deck)), b_isRunning(false),
										allPlayers(std::move(players)), numOfPlayers(allPlayers.size())
{

}

Game::~Game() { }

const Game::Players& Game::getAllPlayers() const {
	return allPlayers;
}

uint32_t Game::numberOfPlayers() const {
	return numOfPlayers;
}

bool Game::isRunning() const {
	return b_isRunning;
}
