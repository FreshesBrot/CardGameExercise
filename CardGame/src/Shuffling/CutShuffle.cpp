#include "CutShuffle.h"
#define CUT_RANGE 5
#define RAND_INT int(RandomGenerator::getInstance()->get() * CUT_RANGE) + 1

CutShuffle::CutShuffle(int cycles) : Shuffler(cycles) { }

void CutShuffle::shuffleDeck(Deck& deck) {
	shuffledDeck.clearDeck();
	newCut.clearDeck();

	for (int i = 0; i < cycles; i++) {
		while (!deck.isEmpty()) {
			Deck::cutIntoDeck(deck, newCut, RAND_INT);
			//newCut = deck.cut(RAND_INT);

			shuffledDeck.mergeDecks(newCut);
		}

		deck.mergeDecks(shuffledDeck);
	}
}
