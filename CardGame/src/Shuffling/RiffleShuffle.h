#pragma once
#include "Shuffler.h"

//this class represents a riffle shuffle
class RiffleShuffle : public Shuffler {
public:
	RiffleShuffle(int cycles = 5);

	//riffle shuffle cuts a deck in half, and then cuts two small number of cards (i.e [1,4]) from each deck from the bottom and merges each new cut onto a new deck
	void shuffleDeck(Deck& deck) override;

private:
	//these are resources the shuffler will need during shuffling
	Deck deck2 = Deck::emptyDeck(); //this deck represents the other half that is riffled into the middle
	Deck shuffledDeck = Deck::emptyDeck(); //this deck represents the deck that gets created when two decks riffle into each other

	Deck cut1 = Deck::emptyDeck(); //this deck represents a chunk of cards from the first half that gets riffled into the middle
	Deck cut2 = Deck::emptyDeck(); //this deck represents a chunk of cards from the second half that gets riffled into the middle
};

