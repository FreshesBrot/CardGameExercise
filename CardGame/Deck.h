#pragma once
#include "Card.h"
#include <list>

//this class represents a deck of 52 cards
class Deck {
public:
	//initializes a full and unshuffled deck
	Deck();
	//initializes a deck from a custom list of cards
	Deck(std::list<Card> cards);
	//move constructor for quick construction of lists
	Deck(Deck&& deck) noexcept;

#pragma region DeckOperations
	//draws the top card. returns invalid card if no cards are remaining.
	Card drawTopCard(); 

	//adds a card to the top of the deck. returns 0 if insert was successfull, and 1 if not.
	int addCard(Card card);

	//cuts this deck in half and returns the other top half as a new Deck
	Deck cut();

	//cuts a specific number of cards from the top of the deck and returns the new deck. will return an empty deck if amount is less than 1 and itself when geq than the deck.
	Deck cut(unsigned int amount);

	//same as cut, but taken from the bottom
	Deck cutBottom();

	//same as cut, but takem from the bottom
	Deck cutBottom(unsigned int amount);

	//merges two decks by putting the argument deck on top of this instance
	void mergeDecks(Deck& deck);

	//Checks if the decks contains the card. if card is invalid or deck is empty, returns false. 
	bool contains(Card& card);

	//sorts the deck in standard suit order and 2,...,A
	void sort();

	//sorts the deck defined by the given comparator
	void sort(bool (*comp)(const Card&, const Card&));

#pragma endregion

	//creates an empty Deck
	static Deck emptyDeck();

	//returns false if the deck still remains cards, and true if there are no more cards.
	bool isEmpty() const;

	//whether this deck is a valid deck or not. a deck is valid if all its cards are valid.
	bool isValid();

	//return the number of cards in this deck.
	int getDeckSize() const;

	//returns a list of all cards - shouldnt be used if order of cards is supposed to be unknown.
	std::list<Card> getCards();

private:
	bool b_isEmpty; //whether the deck is empty.

	std::list<Card> cards; //all cards in the deck.
	unsigned int remainingCards; //number of remaining cards in the deck.

	//helper function that returns a list of cards that are cut from this deck. this function alters the deck size. specify wether to take cards from the top or bottom (0 = top, rest = bottom)
	std::list<Card> cutCardList(int amount, int side = 0);
};

