#pragma once
#include "BaseException.h"

//this exception is thrown when an empty queue is attempted to be accessed

class EmptyQueueException : public BaseException {
public:
	EmptyQueueException() : BaseException("Tried to access an empty Queue.\n") { };
	EmptyQueueException(const Message& msg) : BaseException(msg) { };
	~EmptyQueueException() { };
};