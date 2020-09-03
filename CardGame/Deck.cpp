#include "Deck.h"
#define ISEMPTY if(remainingCards == 0) b_isEmpty = true

Deck::Deck() : b_isEmpty(false), remainingCards(52) {
	for (int i = 1; i < 5; i++)
		for (int j = 2; j < 15; j++)
			cards.push_back(Card(Suite(i), j));
}

Deck::Deck(std::list<Card> cards) : b_isEmpty(cards.empty()), cards(cards), remainingCards(cards.size()) { }

Card Deck::drawTopCard() {
	if (b_isEmpty) return Card(Suite(0),0);

	Card draw = cards.back();
	cards.pop_back();
	b_isEmpty = !(--remainingCards);
	
	return draw;
}

int Deck::addCard(Card card) {
	bool isValid = card.isValid();
	remainingCards += isValid;
	
	if (isValid)
		cards.push_back(card);
	
	return isValid^0x1;
}

Deck Deck::cut() {
	return Deck(cutCardList(remainingCards / 2));
}

Deck Deck::cut(int amount) {
	if (amount<1) return Deck(std::list<Card>());
	if (amount >= remainingCards) {
		remainingCards = 0;
		b_isEmpty = true;
		std::list<Card> newDeck;
		newDeck.splice(newDeck.begin(), cards);
		return Deck(newDeck);
	}
	
	return Deck(cutCardList(amount));
}

bool Deck::isEmpty() const {
	return b_isEmpty;
}

bool Deck::isValid() {
	bool isValid = true;

	for (auto& c : cards)
		if(!(isValid&=c.isValid())) return false;

	return isValid;
}

int Deck::getDeckSize() const {
	return remainingCards;
}

std::list<Card> Deck::getCards() {
	return cards;
}

void Deck::mergeDecks(Deck& deck) {
	remainingCards += deck.getDeckSize();
	b_isEmpty = !remainingCards;

	cards.splice(cards.end(), deck.cards);

	deck.remainingCards = 0;
	deck.b_isEmpty = true;

}

bool Deck::contains(Card& card) {
	if (!card.isValid() || b_isEmpty) return false;
	
	for (Card& c : cards)
		if (card.equals(c)) return true;
	
	return false;
}

std::list<Card> Deck::cutCardList(int amount) {
	auto it = cards.end();
	std::advance(it, -amount);
	std::list<Card> cards2(it, cards.end());
	remainingCards -= amount;
	cards.erase(it, cards.end());
	
	return cards2;
}