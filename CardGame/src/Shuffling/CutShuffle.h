#pragma once
#include "Shuffler.h"

//this class represents a cut shuffling
class CutShuffle : public Shuffler {
public:
	
	CutShuffle(int cycles = 10);

	//cut shuffle cuts a small random number (e.g. [1,5]) of cards from the given deck and puts each cut on top of the previous to form the next cut 
	void shuffleDeck(Deck& deck) override;

private:
	//these are resources the shuffler will need during shuffling
	Deck shuffledDeck = Deck::emptyDeck(); //this deck represents the deck that gets created with each added cut
	Deck newCut = Deck::emptyDeck(); //this deck represents a new chunk of cards from the original deck that gets shuffled onto the shuffledDeck

};

