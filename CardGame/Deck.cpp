#include "Deck.h"
#define IT_BEGIN cards.begin()
#define IT_END cards.end()

Deck::Deck() : b_isEmpty(false), remainingCards(52) {
	for (int i = 1; i < 5; i++)
		for (int j = 2; j < 15; j++)
			cards.push_back(Card(Suite(i), j));
}

Deck::Deck(std::list<Card> cards) : b_isEmpty(cards.empty()), cards(cards), remainingCards(cards.size()) { }

Deck::Deck(Deck&& deck) noexcept : remainingCards(deck.remainingCards), b_isEmpty(deck.b_isEmpty), cards() {
	cards.splice(cards.begin(), deck.cards);
}

Card Deck::drawTopCard() {
	if (b_isEmpty) return Card::Invalid();

	Card draw = std::move(cards.back());
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

Deck Deck::cut(uint32_t amount) {
	if (!amount) return Deck(std::list<Card>());
	if (amount >= remainingCards) {
		remainingCards = 0;
		b_isEmpty = true;
		std::list<Card> newDeck;
		newDeck.splice(newDeck.begin(), cards);
		return Deck(newDeck);
	}
	
	return Deck(cutCardList(amount));
}

Deck Deck::cutBottom() {
	return Deck(cutCardList(remainingCards / 2, 1));
}

Deck Deck::cutBottom(uint32_t amount) {
	if (!amount) return Deck(std::list<Card>());
	if (amount >= remainingCards) {
		remainingCards = 0;
		b_isEmpty = true;
		std::list<Card> newDeck;
		newDeck.splice(newDeck.begin(), cards);
		return Deck(newDeck);
	}

	return Deck(cutCardList(amount, 1));
}

bool Deck::isEmpty() const {
	return b_isEmpty;
}

bool Deck::isValid() const {
	bool isValid = true;

	for (auto& c : cards)
		if(!(isValid&=c.isValid())) return false;

	return isValid;
}

uint32_t Deck::getDeckSize() const {
	return remainingCards;
}

std::list<Card>& Deck::getCards() {
	return cards;
}

void Deck::mergeDecks(Deck& deck) {
	if (deck.isEmpty()) return;
	
	remainingCards += deck.getDeckSize();
	b_isEmpty = !remainingCards;

	cards.splice(cards.end(), deck.cards);

	deck.remainingCards = 0;
	deck.b_isEmpty = true;

}

bool Deck::contains(const Card& card) const {
	if (!card.isValid() || b_isEmpty) return false;
	
	for (const Card& c : cards)
		if (card == c) return true;
	
	return false;
}

void Deck::sort() {
	//sorting !higherCard has the highest card on top, meaning its sorted lowest to highest
	cards.sort([](const Card& c1, const Card& c2) {
			return !Card::higherCard(c1, c2);
		});
}

void Deck::sort(bool(*comp)(const Card&, const Card&)) {
	cards.sort(comp);
}

std::list<Card> Deck::cutCardList(int amount, int side) {

	std::list<Card> cards2;

	if (side) { //handle cutting from the bottom
		auto it = IT_BEGIN;
		std::advance(it, amount);
		cards2 = std::list<Card>(IT_BEGIN, it);
		cards.erase(IT_BEGIN, it);
	
	} else { //handle cutting from the top
		auto it = IT_END;
		std::advance(it, -amount);
		cards2 = std::list<Card>(it, IT_END);
		cards.erase(it, IT_END);
	}

	remainingCards -= amount;
	return cards2;
}