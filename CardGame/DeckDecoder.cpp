#include "DeckDecoder.h"

DeckDecoder::DeckDecoder(byte* dataBlock, size_t blockSize) : dataBlock(dataBlock), blockSize(blockSize) { }

Deck DeckDecoder::Decode() {
	std::list<Card> cards;
	for (auto i = 0u; i < blockSize; i++)
		cards.push_back(CardDecoder::Decode(dataBlock[i]));

	return Deck(cards);
}
