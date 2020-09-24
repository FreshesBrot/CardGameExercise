#pragma once
#include <exception>
#include <string>

typedef std::exception Exception;

//this is the base class for all exceptions
class BaseException : Exception {
public:
	typedef std::string Message;
	
	BaseException() : errMessage("An Exception occured.\n") { };
	BaseException(const Message& msg) : errMessage(msg) { };
	~BaseException() {};

	const char* what() const override {
		return errMessage.c_str();
	}

protected:
	Message errMessage;
};

