#pragma once
#include "Shuffler.h"
class RiffleShuffle : public Shuffler {
	RiffleShuffle();
	RiffleShuffle(int cycles);

	void shuffleDeck(Deck& deck) override;
};

