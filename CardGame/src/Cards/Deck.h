#pragma once
#include "Card.h"
#include "../../../Exceptions/src/Exceptions/DeckException.h"
#include <list>

typedef std::list<Card> Cards;

#pragma region DeckIterator
//iterator that iterates through the card elements
class DeckIterator {
	typedef std::list<Card>::const_iterator __DeckIterator;
public:
	DeckIterator(const __DeckIterator& iter) : cur(iter) { };

	__DeckIterator& operator++() {
		return ++cur;
	}

	__DeckIterator operator++(int) {
		__DeckIterator tmp = cur;
		cur++;
		return tmp;
	}

	bool operator==(const DeckIterator& it) const {
		return cur == it.cur;
	}

	bool operator!=(const DeckIterator& it) const {
		return !(*this == it);
	}

	const Card& operator*() {
		return *cur;
	}

	const Card* operator->() {
		return &(*cur);
	}

private:
	__DeckIterator cur;
};
#pragma endregion

//this class represents a deck of cards
class Deck {
public:

	//initializes a deck from a custom list of cards
	Deck(Cards&& cards);

	//decks are not supposed to be copied
	Deck(const Deck&) = delete;
	Deck& operator=(const Deck&) = delete;

	//move constructor for quick construction of lists from returned anonymous decks
	Deck(Deck&& deck) noexcept;
	Deck& operator=(Deck&& deck) noexcept;


#pragma region DeckOperations
	//draws the top card. throws a DeckException if the deck is empty.
	Card drawTopCard(); 

	//adds a card to the top of the deck. An invalid card will not be added to the deck.
	void addCard(const Card& card);

	//cuts this deck in half and returns the other top half as a new Deck
	Deck cut();

	//cuts a specific number of cards from the top of the deck and returns the new deck. will return an empty deck if amount is less than 1 and itself when geq than the deck.
	Deck cut(uint32_t amount);

	//same as cut, but taken from the bottom
	Deck cutBottom();

	//same as cut, but takem from the bottom
	Deck cutBottom(uint32_t amount);

	//merges two decks by putting the argument deck on top of this instance
	void mergeDecks(Deck& deck);

	//Checks if the decks contains the card. if card is invalid or deck is empty, returns false. 
	bool contains(const Card& card) const;

	//sorts the deck in standard suit order and 2,...,A
	void sort();

	//sorts the deck defined by the given comparator
	void sort(bool (*comp)(const Card&, const Card&));

	//static function that takes a source deck and cuts half of the deck into the destination deck. this will clear the destination deck
	static void cutIntoDeck(Deck& src, Deck& dst);

	//static function that takes a source deck and cuts amt of the deck into the destination deck. this will clear the destination deck
	static void cutIntoDeck(Deck& src, Deck& dst, uint32_t amt);

	//static function that takes a source deck and cuts half of the deck from the bottom into the destination deck. this will clear the destination deck
	static void cutBottomIntoDeck(Deck& src, Deck& dst);

	//static function that takes a source deck and cuts amt of the deck from the bottom into the destination deck. this will clear the destination deck
	static void cutBottomIntoDeck(Deck& src, Deck& dst, uint32_t amt);

	//clears all cards in the deck
	void clearDeck();
#pragma endregion

	//creates an empty Deck
	inline static Deck emptyDeck() { return Deck(Cards()); };

	//creates a default deck
	inline static Deck defaultDeck() { return Deck(defaultCards); }

	//returns false if the deck still remains cards, and true if there are no more cards.
	bool isEmpty() const;

	//whether this deck is a valid deck or not. a deck is valid if all its cards are valid.
	bool isValid() const;

	//return the number of cards in this deck.
	uint32_t getDeckSize() const;

	DeckIterator begin();

	DeckIterator end();


private:
	bool b_isEmpty; //whether the deck is empty.

	Cards cards; //all cards in the deck.
	uint32_t remainingCards; //number of remaining cards in the deck.

	//helper function that returns a list of cards that are cut from this deck. this function alters the deck size. specify wether to take cards from the top or bottom (0 = top, rest = bottom)
	Cards cutCardList(int amount, int side = 0);
	
	//this helper function will initialize the default deck
	static Cards initDefault();
	static Cards defaultCards; //variable that just holds all standard cards in standard order
	
	//private constructor that takes copyable card lists
	Deck(const Cards& cards);
};

