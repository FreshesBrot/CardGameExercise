#pragma once
#include "Deck.h"
#include "RandomGenerator.h"

//this class provides an interface for classes to shuffle a deck, as well as a random number generator.
class Shuffler {
protected:
	Shuffler(int cycles);

	//virtual function that all shuffle algorithms inherit.
	virtual void shuffleDeck(Deck& deck) = 0;

	const int cycles; //number of shuffle cycles for each shuffler instance.
};

