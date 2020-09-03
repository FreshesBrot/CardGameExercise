#include "Card.h"

Card::Card(Suite suite, unsigned int number) {
	bool eval = !(number < 2 || number > 14 || suite == 0);
	this->suite = Suite(suite * eval);
	this->number = number * eval;
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

bool Card::equals(Card& card) {
	if(b_isValid && card.b_isValid)
	return (number == card.number) && (suite == card.suite);

	return false;
}

const std::string Card::suites[] = { "INVALID","HEARTS","DIAMONDS","CLUBS","SPADES" };
const std::string Card::suitesShort[] = { "F","H","D","C","S" };

const std::string Card::numbers[] = { "INVALID","INVALID","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE","TEN","JACK","QUEEN","KING","ACE" };
const std::string Card::numbersShort[] = { "F","F","2","3","4","5","6","7","8","9","10","J","Q","K","A" };