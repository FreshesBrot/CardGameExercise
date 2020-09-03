// CardGame.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "FileWriter.h"
#include "FileReader.h"

#include "Card.h"
#include "Deck.h"
#include "CutShuffle.h"
#include "DeckEncoder.h"
#include "DeckDecoder.h"
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
	std::list<Card> cards = {Card(Suite(1),2), Card(Suite(1),3), Card(Suite(1),4), Card(Suite(1),5)};
	Deck deck;
	CutShuffle shuffle(25);
	shuffle.shuffleDeck(deck);
	
	DeckEncoder encoder(deck);
	encoder.encodeDeck();

	FileWriter fw(L"deck.deckf");
	fw.Write();
	fw.writeData(encoder.getData(), encoder.getBlockSize());
	fw.Close();

	drawDeck(deck);

	std::cout << "wrote deck to " << DECKFILE << NL;

	FileReader fr(L"deck.deckf");
	fr.Read();
	size_t deckSize = fr.getBlockSize();
	byte* deckData = new byte[deckSize];
	fr.readBlock(deckData, deckSize);
	fr.Close();
	
	DeckDecoder decoder(deckData, deckSize);
	Deck decodedDeck = decoder.Decode();

	delete[] deckData;

	drawDeck(decodedDeck);

	std::cout << "Read Deck from " << DECKFILE << NL;


	system("pause");
}

