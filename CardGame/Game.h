#pragma once
#include "Deck.h"
#include "IOParser.h"
#include "Hand.h"
#include "ShuffleEngine.h"

//TODOS: the games should have a unordered map with game states mapping to the apropriate commands

//base class for all card games that can be run
class Game {
protected:
public:
	typedef std::vector<Hand> Players;
	typedef std::vector<IOParser> GameStates;
	
	~Game();

	//used by inheriting classes to set up the start of a game
	virtual void start() = 0;
	//used by inheriting classes to finish the game and free all resources
	virtual void end() = 0;

	//return a const reference to all players in this game instance
	const Players& getAllPlayers() const;

	//return the number of players in this game instance
	uint32_t numberOfPlayers() const;

	//returns if the game is currently (supposed) to be running
	bool isRunning() const;

protected:
	//Internal shuffle engine all games can use
	static ShuffleEngine shuffleEngine;

	//constructor is private, so that each game instance can initiate everything that is needed by itself
	Game(Deck& deck, Players players);
	
	bool b_isRunning; //flag that determines if the game should be running or not

	//function that will initiate the command parser. needs to be implemented by each 
	virtual void setup() = 0;
	
	//function that all game instances need to define - defines the main game loop
	virtual void gameLoop() = 0;

	GameStates commandParser; //internal vector of command parsers used by this game instance
	TokenVector helperMessages; //helper messages containing each parser's helper message

	Deck playingDeck; //the deck that is used to play the game
	Players allPlayers; //all players in this game
	uint32_t numOfPlayers; //number of participating players in this game instance

	
};

