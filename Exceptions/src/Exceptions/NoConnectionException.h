#pragma once
#include "BaseException.h"

//class that represents card errors of any capacity
class NoConnectionException : public BaseException {
public:
	NoConnectionException() : BaseException("An error during Card handling occured.") { }
	NoConnectionException(const Message& msg) : BaseException(msg) { };
	~NoConnectionException() { }
};