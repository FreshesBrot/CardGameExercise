#include "Card.h"
#define CALC_ID (int)order[(int)this->suite] * 13 + this->number

Card::Card(Suite suite, unsigned int number) : suite(Suite::INVALID), number(0), b_isValid(false), cardID(0) {
	if(number < 2 || number > 14) return;
	this->suite = suite;
	this->number = number;
	this->cardID = CALC_ID;
	this->b_isValid = true;
}

Card::Card() : suite(Suite(1)), number(2), b_isValid(1), cardID(CALC_ID) { }

Card Card::toCard(std::string arg) {
	if (arg.size() < 2 || arg.size() > 3)
		throw CardException("Provided argument \"" + arg + "\" could not be parsed into a card!");

	char suiteBit = *(arg.end() - 1);
	Suite suite = Suite::INVALID;
	//first determine the suite
	switch (suiteBit) {
	case 'H':
		suite = Suite::HEARTS;
		break;
	case 'D':
		suite = Suite::DIAMONDS;
		break;
	case 'C':
		suite = Suite::CLUBS;
		break;
	case 'S':
		suite = Suite::SPADES;
		break;
	default:
		break;
	}

	int number = std::stoi(arg.substr(0,arg.size()-2)); //get rest of string (from [0,0] if size == 2 (single char), or [0,1] if size == 3)
	Card card(suite, number);
	if (!card.isValid())
		throw CardException("Provided argument \"" + arg + "\" could not be parsed into a card!");

	return card;
}

Suite Card::getSuite() const {
	return suite;
}

uint32_t Card::getNumber() const {
	return number;
}

bool Card::isValid() const {
	return b_isValid;
}

std::string Card::toString() const {
	return numbers[number] + " OF " + suites[(int)suite];

}

std::string Card::shortString() const {
	return numbersShort[number] + suitesShort[(int)suite];
}

bool Card::operator==(const Card& card) const {
	return card.cardID == cardID;
}

bool Card::operator!=(const Card& card) const {
	return !(*this == card);
}

bool Card::higherSuite(const Card& c1, const Card& c2) {
	return order[(int)c1.suite] > order[(int)c2.suite];
}

bool Card::higherNumber(const Card& c1, const Card& c2) {
	return c1.number > c2.number;
}

bool Card::higherCard(const Card& c1, const Card& c2) {
	return c1.cardID > c2.cardID;
}

const std::string Card::suites[] = { "INVALID","HEARTS","DIAMONDS","CLUBS","SPADES" };
const std::string Card::suitesShort[] = { "F","H","D","C","S" };

const std::string Card::numbers[] = { "INVALID","INVALID","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE","TEN","JACK","QUEEN","KING","ACE" };
const std::string Card::numbersShort[] = { "F","F","2","3","4","5","6","7","8","9","10","J","Q","K","A" };

const Suite Card::order[] = { Suite::INVALID, Suite::HEARTS, Suite::DIAMONDS, Suite::CLUBS, Suite::SPADES };