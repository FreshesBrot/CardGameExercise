#include "Card.h"

Card::Card(Suite suite, unsigned int number) {
	bool eval = !(number < 2 || number > 14 || suite == 0);
	this->suite = Suite(suite * eval);
	this->number = number * eval;
	this->cardID = order[this->suite] * 13 + this->number;
	this->b_isValid = eval;
}

Suite Card::getSuite() {
	return suite;
}

unsigned int Card::getNumber() {
	return number;
}

bool Card::isValid() {
	return b_isValid;
}

std::string Card::toString() {
	return numbers[number] + " OF " + suites[suite];

}

std::string Card::shortString() {
	return numbersShort[number] + suitesShort[suite];
}

bool Card::equals(const Card& card) {
	if(b_isValid && card.b_isValid)
	return (number == card.number) && (suite == card.suite);

	return false;
}

bool Card::higherSuite(const Card& c1, const Card& c2) {
	return order[c1.suite] > order[c2.suite];
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