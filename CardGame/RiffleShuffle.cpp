#include "RiffleShuffle.h"

RiffleShuffle::RiffleShuffle() : Shuffler(5) { }

RiffleShuffle::RiffleShuffle(int cycles) : Shuffler(cycles) { }

void RiffleShuffle::shuffleDeck(Deck& deck) {
	for (int i = 0; i <= cycles; i++) {
		Deck cutDeck = deck.cut();


	}
}