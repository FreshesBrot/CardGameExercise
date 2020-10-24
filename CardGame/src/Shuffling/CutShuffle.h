#pragma once
#include "Shuffler.h"

//this class represents a cut shuffling
class CutShuffle : public Shuffler {
public:
	CutShuffle();
	CutShuffle(int cycles);

	//cut shuffle cuts a small random number (e.g. [1,5]) of cards from the given deck and puts each cut on top of the previous to form the next cut 
	void shuffleDeck(Deck& deck) override;
};

