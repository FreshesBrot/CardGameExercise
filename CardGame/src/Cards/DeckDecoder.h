#pragma once
#include "CardDecoder.h"
#include "Deck.h"

//this class is responsible for decoding an entire deck and storing the result as a list
class DeckDecoder {
public:
	//initialize decoder with given values
	DeckDecoder(byte* dataBlock, size_t blockSize);

	//decode the datablock and retrieve the deck
	Deck Decode();

private:
	byte* dataBlock; //this array is not managed by this class
	size_t blockSize;
};

