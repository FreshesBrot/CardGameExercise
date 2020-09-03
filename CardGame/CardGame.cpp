// CardGame.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

#include "Deck.h"
#include "DeckLoader.h"
#include "CutShuffle.h"
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


int main() {
	//std::list<Card> cards = {Card(Suite(1),2), Card(Suite(1),3), Card(Suite(1),4), Card(Suite(1),5)};
	Deck deck;
	CutShuffle shuffle(25);
	shuffle.shuffleDeck(deck);
	
	DeckLoader save(DECKFILE, DeckLoader::LoaderMode::SAVE);
	save.saveDeck(deck);

	DeckLoader load(DECKFILE, DeckLoader::LoaderMode::LOAD);
	Deck loadedDeck = load.loadDeck();

	drawDeck(deck);
	drawDeck(loadedDeck);

	system("pause");
}

