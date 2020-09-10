// CardGame.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Language Standard: C++17

#include <iostream>
#define OUT std::cout

#include "Hand.h"
#include "Deck.h"
#include "DeckLoader.h"
#include "ShuffleEngine.h"
#define CARDCODE(code) printf("0x%02X\n", code)
#define DECKFILE "deck.deckf"
#define NL "\n"

#pragma region Card/Deck Functions
void showHand(Hand& hand) {
	OUT << "Current Hand: " << NL;
	auto cards = hand.getCards();
	for (int i = 0; i < hand.getRemainingCards(); i++)
		OUT << cards[i].shortString() << " ";

	OUT << NL;
}
void drawDeck(Deck& deck) {
	int count = 12;
	while (!deck.isEmpty()) {
		OUT << deck.drawTopCard().shortString() << " " ;

		if (--count < 0) {
			OUT << NL;
			count = 12;
		}
	}

	OUT << NL;
}

void peekDeck(Deck& deck) {
	int count = 12;
	for (auto& c : deck.getCards()) {
		OUT << c.shortString() << " ";

		if (--count < 0) {
			OUT << NL;
			count = 12;
		}
	}

	OUT << NL;
}
#pragma endregion

int main() {
	Hand myHand;
	DeckLoader loader(DECKFILE, DeckLoader::LoaderMode::LOAD);
	Deck deck = loader.loadDeck();

	for (int i = 0; i < 5; i++)
		myHand.addCard(deck.drawTopCard());

	drawDeck(deck);
	showHand(myHand);
}

