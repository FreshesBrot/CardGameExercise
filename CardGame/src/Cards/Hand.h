#pragma once
#include "Card.h"
#include <vector>

//this class represents a player's hand and the cards they can play
class Hand {
public:
	//hands are always initialized with no cards
	Hand();
	//hands should not be copied
	Hand(const Hand&) = delete;
	//moving one hand to another is possivble
	Hand(Hand&&) = default;

	//getters
	uint32_t getRemainingCards() const;
	bool isEmpty() const;
	//returns the vector containing all cards on this hand - cards cannot be modified from this reference.
	const std::vector<Card>& getCards() const;


	//removes a card from the players hand and returns that card
	Card playCard(uint32_t index);
	
	//adds a card to the hand - if the card is invalid, it is not added
	void addCard(Card card);

	//move a card from one spot to another
	void swap(uint32_t spot1,uint32_t spot2);

	
private:
	std::vector<Card> cards; //array of all cards
	uint32_t remainingCards; //number of cards on hand
	bool b_emptyHand; //if the hand is empty

};

