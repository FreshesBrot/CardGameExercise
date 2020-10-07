#pragma once
#include "Game.h"

//this game is a simple guessing game, where the player has to guess if the next card that is drawn is higher or lower
class HigherGame : public Game {
public:
	HigherGame(Deck& deck);
	~HigherGame();

	void start() override;
	void end() override;

private:
	void gameLoop() override;

	void setup() override;

	//MEMBERS FOR GAME STATE MANAGEMENT
	enum class GameState {
		MENU = 0,
		GUESSING,
		DRAWING,
	};

	GameState curState; //current state of the game
	
	uint32_t numLives; //number of lives left 
	uint32_t numOfCards; //number of cards that have been guessed correct
	Card curCard; //the current card that has been drawn
	Deck discardPile; //the deck where already drawn cards go
	
	bool b_greeting; //flag to determine if the player needs to be greeted.

	static constexpr int defaultLives = 3;

};

