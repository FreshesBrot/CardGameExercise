#include "CutShuffle.h"
#define CUT_RANGE 5

WaterfallShuffle::WaterfallShuffle() : Shuffler(15) { };
WaterfallShuffle::WaterfallShuffle(int cycles) : Shuffler(cycles) { };

void WaterfallShuffle::shuffleDeck(Deck& deck) {
	for (int i = 0; i <= cycles; i++) {
		Deck cutDeck = deck.cut((int)CUT_RANGE * RandomGenerator::getInstance()->get() + 1);
		deck = cutDeck.mergeDecks(cutDeck);
	}
}
