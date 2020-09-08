// CardGame.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

#include "Deck.h"
#include "DeckLoader.h"
#include "ShuffleEngine.h"
#define CARDCODE(code) printf("0x%02X\n", code)
#define DECKFILE "deck.deckf"
#define NL "\n"

void drawDeck(Deck& deck) {
	int count = 12;
	while (!deck.isEmpty()) {
		std::cout << deck.drawTopCard().shortString() << " " ;

		if (--count < 0) {
			std::cout << "\n";
			count = 12;
		}
	}

	std::cout << "\n";
}

void peekDeck(Deck& deck) {
	int count = 12;
	for (auto&c : deck.getCards()) {
		std::cout << c.shortString() << " ";

		if (--count < 0) {
			std::cout << "\n";
			count = 12;
		}
	}

}


int main() {
	Deck deck;

	ShuffleEngine engine(4);

	engine.ShuffleDeck(deck);

	drawDeck(deck);

	system("pause");

}

