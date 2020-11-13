#include "Deck.h"
#define IT_BEGIN cards.begin()
#define IT_END cards.end()


Deck::Deck(Cards&& cards) : b_isEmpty(), cards(std::move(cards)), remainingCards() { 
	b_isEmpty = this->cards.size();
	remainingCards = this->cards.size();
}

Deck::Deck(const Cards& cards) : cards(cards) {
	remainingCards = this->cards.size();
	b_isEmpty = cards.empty();
}

Deck::Deck(Deck&& deck) noexcept : remainingCards(), b_isEmpty(), cards() {
	*this = std::move(deck);
}

Deck& Deck::operator=(Deck&& deck) noexcept {
	if (this == &deck) return *this;
	cards.clear();
	
	cards = std::move(deck.cards);
	remainingCards = cards.size();
	b_isEmpty = cards.empty();
	
	deck.remainingCards = 0;
	deck.b_isEmpty = true;
	
}

Card Deck::drawTopCard() {
	if (b_isEmpty)
		throw DeckException("Attempting to draw a Card from an empty Deck!");

	Card draw = std::move(cards.back());
	cards.pop_back();
	b_isEmpty = !(--remainingCards);
	
	return draw;
}

void Deck::addCard(const Card& card) {
	if (!card.isValid()) return;
	cards.push_back(card);
	remainingCards++;
	b_isEmpty = false;
}

Deck Deck::cut() {
	return cut(remainingCards/2);
}

Deck Deck::cut(uint32_t amount) {
	if (!amount)
		return Deck(Cards());
	if (amount >= remainingCards)
		return std::move(*this);


	return Deck(std::move(cutCardList(amount)));
}

Deck Deck::cutBottom() {
	return cutBottom(remainingCards/2);
}

Deck Deck::cutBottom(uint32_t amount) {
	if (!amount) 
		return Deck(Cards());
	if (amount >= remainingCards) 
		return std::move(*this);

	return Deck(std::move(cutCardList(amount, 1)));
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

DeckIterator Deck::begin() {
	return DeckIterator(cards.begin());
}

DeckIterator Deck::end() {
	return DeckIterator(cards.end());
}

void Deck::mergeDecks(Deck& deck) {
	if (deck.isEmpty()) return;
	b_isEmpty = false;
	
	remainingCards += deck.getDeckSize();

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

void Deck::cutIntoDeck(Deck& src, Deck& dst) {
	Deck::cutIntoDeck(src, dst, src.remainingCards / 2);
}

void Deck::cutIntoDeck(Deck& src, Deck& dst, uint32_t amt) {
	//make sure its not splicing into itself
	if (&src == &dst) return;
	//then make sure amt is >0
	if (!amt) return;
	//then if amt > src.remainingCards move src deck into dst deck
	if (amt > src.remainingCards) {
		dst = std::move(src);
		return;
	}



	//this should be 0 allocations
	dst.cards.clear();
	Cards::iterator it = src.cards.end();
	std::advance(it, -(int)amt);
	dst.cards.splice(dst.cards.begin(), src.cards, it, src.cards.end());

	src.remainingCards -= amt;
	src.b_isEmpty = src.cards.empty();
	dst.remainingCards += amt;
	dst.b_isEmpty = false;
}

void Deck::cutBottomIntoDeck(Deck& src, Deck& dst) {
	cutBottomIntoDeck(src, dst, src.remainingCards / 2);
}

void Deck::cutBottomIntoDeck(Deck& src, Deck& dst, uint32_t amt) {
	//make sure its not splicing into itself
	if (&src == &dst) return;
	//then make sure amt is >0
	if (!amt) return;
	//then if amt > src.remainingCards move src deck into dst deck
	if (amt > src.remainingCards) {
		dst = std::move(src);
		return;
	}

	//this should be 0 allocations
	dst.cards.clear();
	Cards::iterator it = src.cards.begin();
	std::advance(it, amt);
	dst.cards.splice(dst.cards.begin(), src.cards, src.cards.begin(), it);

	src.remainingCards -= amt;
	src.b_isEmpty = src.cards.empty();
	dst.remainingCards += amt;
	dst.b_isEmpty = false;
}

void Deck::clearDeck() {
	cards.clear();
	remainingCards = 0;
	b_isEmpty = true;
}

Cards Deck::cutCardList(int amount, int side) {

	Cards cards2;

	if (side) { //handle cutting from the bottom
		auto it = IT_BEGIN;
		std::advance(it, amount);
		cards2.splice(cards2.begin(), cards, IT_BEGIN, it);
	} else { //handle cutting from the top
		auto it = IT_END;
		std::advance(it, -amount);
		cards2.splice(cards2.begin(), cards, it, IT_END);
	}

	remainingCards -= amount;
	return cards2;
}

Cards Deck::initDefault() {
	Cards cards;

	for (int i = 1; i < 5; i++)
		for (int j = 2; j < 15; j++)
			cards.push_back(Card(Suite(i), j));
	
	return cards;
}

//this will call initDefault when static runtime variables are constructed
Cards Deck::defaultCards = Deck::initDefault();