#pragma once
#include "CardEncoder.h"
#include "Deck.h"

//this class is responsible for encoding an entire deck and storing the result as char*
class DeckEncoder {
public:
	DeckEncoder(Deck& deck);
	~DeckEncoder();

	void encodeDeck() const;

	byte* getData();
	size_t getBlockSize();

private:
	Deck& deck;
	byte* dataBlock;
	size_t blockSize;
};

