#include "Hand.h"

Hand::Hand() : cards(0), remainingCards(0), b_emptyHand(1) { }

Card Hand::playCard(uint32_t index) {
	if (index >= remainingCards || b_emptyHand) return Card::Invalid();
	Card ret = std::move(cards[index]);
	cards.erase(cards.begin() + index);
	b_emptyHand = !--remainingCards;
	
	return ret;
}

void Hand::addCard(Card card) {
	if (!card.isValid()) return;

	cards.push_back(card);
	b_emptyHand = !++remainingCards;

}

void Hand::swap(uint32_t spot1, uint32_t spot2) {
	Card& c = cards[spot1];
	cards[spot1] = cards[spot2];
	cards[spot2] = c;
}

uint32_t Hand::getRemainingCards() const {
	return remainingCards;
}

bool Hand::isEmpty() const {
	return b_emptyHand;
}

const std::vector<Card>& Hand::getCards() const {
	return cards;
}
