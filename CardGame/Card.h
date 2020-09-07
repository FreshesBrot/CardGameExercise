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

#pragma region Comparators
	//checks if a card is equal to this instance of card. invalid cards always return false.
	bool equals(const Card& card); 

	//checks if card c1 has a higher suite than card c2
	static bool higherSuite(const Card& c1,const Card& c2);

	//checks if card c1 has a higher number than card c2
	static bool higherNumber(const Card& c1,const Card& c2);

	//checks if card c1 has both the higher suite and the higher number
	static bool higherCard(const Card& c1, const Card& c2);
	
#pragma endregion

private:
	Suite suite; //suite of the card
	unsigned int number; //numbers 11-13 are J,Q,K,A, 0 is invalid
	bool b_isValid; // if the card is valid or not
	short cardID; //stores the ID of the card. ids are calculated at runtime and depend on the suite ordering. cardID of 0 is invalid

	//arrays containing values to construct string messages
	static const std::string suites[];
	static const std::string suitesShort[];

	static const std::string numbers[];
	static const std::string numbersShort[];

	//array containing the suite order - can be changed and allows for variable suite orders
	static const Suite order[];
};

