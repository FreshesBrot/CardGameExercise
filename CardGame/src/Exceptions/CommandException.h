#pragma once
#include "BaseException.h"

//class that represents an error during parsing or similar
class CommandException : public BaseException {
public:
	CommandException() : BaseException("Something with parsing went wrong.\n") { };
	CommandException(const Message& msg) : BaseException(msg) { };
	~CommandException() { };
};