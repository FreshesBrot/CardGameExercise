#include "CutShuffle.h"
#define CUT_RANGE 5

CutShuffle::CutShuffle() : Shuffler(10) { }
CutShuffle::CutShuffle(int cycles) : Shuffler(cycles) { }

void CutShuffle::shuffleDeck(Deck& deck) {
	for (int i = 0; i < cycles; i++) {
		Deck cutDeck = deck.cut(RandomGenerator::getInstance()->get() * CUT_RANGE + 1);
		
		while (!deck.isEmpty()) {
			Deck newCut = deck.cut(RandomGenerator::getInstance()->get() * CUT_RANGE + 1);
			cutDeck.mergeDecks(newCut);
		}

		deck.mergeDecks(cutDeck);
	}
}
