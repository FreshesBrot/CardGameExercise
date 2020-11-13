#include "RiffleShuffle.h"
#define CUT_RANGE 4
#define RAND_INT int(RandomGenerator::getInstance()->get() * CUT_RANGE) + 1


RiffleShuffle::RiffleShuffle(int cycles) : Shuffler(cycles) { }

void RiffleShuffle::shuffleDeck(Deck& deck) {
	deck2.clearDeck();
	shuffledDeck.clearDeck();

	cut1.clearDeck();
	cut2.clearDeck();

	for (int i = 0; i <= cycles; i++) {
		Deck::cutIntoDeck(deck, deck2);
		//deck2 = deck.cut();
		
		while (!(deck.isEmpty() || deck2.isEmpty())) {

			for (int i = 0; i <= cycles; i++) {
				//cut1 = deck.cutBottom(RAND_INT);
				Deck::cutBottomIntoDeck(deck, cut1, RAND_INT);
				//cut2 = deck2.cutBottom(RAND_INT);
				Deck::cutBottomIntoDeck(deck2, cut2, RAND_INT);
				cut1.mergeDecks(cut2);

				shuffledDeck.mergeDecks(cut1);
			}
			
			deck.mergeDecks(deck2);
			deck.mergeDecks(shuffledDeck);
		}
	}
}