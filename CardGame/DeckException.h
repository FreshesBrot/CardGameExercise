#pragma once
#include "BaseException.h"

//this class represents errors that are thrown when a deck operation fails
class DeckException : public BaseException {
public:
	DeckException() : BaseException("A Deck operation went wrong.") { };
	DeckException(const Message& errorMsg) : BaseException(errorMsg) { };
	~DeckException() { };
};