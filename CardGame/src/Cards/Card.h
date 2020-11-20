#pragma once
#include <string>
#include "../../../Exceptions/src/Exceptions/CardException.h"

//enum that holds all suits for the cards
enum class Suite {
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
	Card(Suite suite, uint32_t number);
	//will construct a 2 of hearts
	Card();
	//cards cannot be copied
	Card(const Card&) = default;
	Card(Card&&) = default;

	//constructs an invalid card
	inline static Card Invalid() { return Card(Suite::INVALID, 0); };

	//tries to convert a (short!!) string card representation into a card object. throws an exception if conversion fails
	static Card toCard(const std::string& arg);

	//getters (cards will not change after intialization)
	
	Suite getSuite() const;
	uint32_t getNumber() const;
	bool isValid() const;

	//represents the card in string format
	std::string toString() const;
	//represents the card as a shorter string
	std::string shortString() const; 

#pragma region Comparators
	bool operator==(const Card& card) const;

	bool operator!=(const Card& card) const;

	//checks if card c1 has a higher suite than card c2
	static bool higherSuite(const Card& c1,const Card& c2);

	//checks if card c1 has a higher number than card c2
	static bool higherNumber(const Card& c1,const Card& c2);

	//checks if card c1 has both the higher suite and the higher number
	static bool higherCard(const Card& c1, const Card& c2);
	
#pragma endregion

	Card& operator=(const Card&) = default;

private:
	Suite suite; //suite of the card
	uint32_t number; //numbers 11-13 are J,Q,K,A, 0 is invalid
	bool b_isValid; // if the card is valid or not
	uint8_t cardID; //stores the ID of the card. ids are calculated at runtime and depend on the suite ordering. cardID of 0 is invalid

	//arrays containing values to construct string messages
	static const std::string suites[];
	static const std::string suitesShort[];

	static const std::string numbers[];
	static const std::string numbersShort[];

	//array containing the suite order - can be changed and allows for variable suite orders
	static const Suite order[];
};

