#include "DeckEncoder.h"

DeckEncoder::DeckEncoder(Deck& deck) : deck(deck), blockSize(deck.getDeckSize()) {
	dataBlock = new byte[blockSize];
}

DeckEncoder::~DeckEncoder() {
	delete[] dataBlock;
}

void DeckEncoder::encodeDeck() const {
	int count = 0;
	for (auto& c : deck.getCards())
		dataBlock[count++] = CardEncoder::Encode(c);
}

byte* DeckEncoder::getData() {
	return dataBlock;
}

size_t DeckEncoder::getBlockSize() {
	return blockSize;
}
