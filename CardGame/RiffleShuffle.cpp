#include "RiffleShuffle.h"
#define CUT_RANGE 4
#define RAND_INT RandomGenerator::getInstance()->get() * CUT_RANGE + 1


RiffleShuffle::RiffleShuffle() : Shuffler(5) { }

RiffleShuffle::RiffleShuffle(int cycles) : Shuffler(cycles) { }

void RiffleShuffle::shuffleDeck(Deck& deck) {
	for (int i = 0; i <= cycles; i++) {
		Deck deck2 = deck.cut();
		Deck shuffledDeck = Deck::emptyDeck();

		while (!(deck.isEmpty() || deck2.isEmpty())) {
			Deck cut1 = deck.cutBottom(RAND_INT);
			Deck cut2 = deck2.cutBottom(RAND_INT);
			cut1.mergeDecks(cut2);

			shuffledDeck.mergeDecks(cut1);
		}
		
		deck.mergeDecks(deck2);
		deck.mergeDecks(shuffledDeck);
	}
}