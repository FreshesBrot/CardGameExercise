#pragma once
#include <string>


//enum that holds all suits for the cards
enum Suite {
	INVALID = 0,
	HEARTS,
	DIAMONDS,
	CLUBS,
	SPADES
};

//this class represents a playing card
class Card {
public:
	//constructs a new card. number values outside of [2,14] are invalid.
	Card(Suite suite, unsigned int number);

	//getters (cards will not change after intialization)
	
	Suite getSuite();
	unsigned int getNumber();
	bool isValid();

	//represents the card in string format
	std::string toString();
	//represents the card as a shorter string
	std::string shortString(); 

	//checks if a card is equal to this instance of card. invalid cards always return false.
	bool equals(Card& card); 

private:
	Suite suite;
	unsigned int number; //numbers 11-13 are J,Q,K,A, 0 is invalid
	bool b_isValid;

	//arrays containing values to construct string messages
	static const std::string suites[];
	static const std::string suitesShort[];

	static const std::string numbers[];
	static const std::string numbersShort[];
};

