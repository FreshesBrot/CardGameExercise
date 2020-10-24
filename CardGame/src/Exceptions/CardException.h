#pragma once
#include "BaseException.h"

//class that represents card errors of any capacity
class CardException : public BaseException {
public:
	CardException() : BaseException("An error during Card handling occured.") { }
	CardException(const Message& msg) : BaseException(msg) { };
	~CardException() { }
};

