#pragma once
#include "Shuffler.h"

//this class represents a riffle shuffle
class RiffleShuffle : public Shuffler {
public:
	RiffleShuffle();
	RiffleShuffle(int cycles);

	//riffle shuffle cuts a deck in half, and then cuts two small number of cards (i.e [1,4]) from each deck from the bottom and merges each new cut onto a new deck
	void shuffleDeck(Deck& deck) override;
};

