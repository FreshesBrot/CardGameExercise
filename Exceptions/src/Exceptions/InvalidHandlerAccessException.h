#pragma once
#include "BaseException.h"

//this exception is thrown when a class tries to access an invalid (response) handler
class InvalidHandlerAccessException : public BaseException {
public:
	InvalidHandlerAccessException() : BaseException("Tried to access and invalid handler.") { };
	InvalidHandlerAccessException(const Message& msg) : BaseException(msg) { };
	~InvalidHandlerAccessException() { };
};