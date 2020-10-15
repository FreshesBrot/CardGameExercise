#pragma once
#include "CommandTypes.h"


//this enumerator is used to classify what argument types are expected
enum class ArgType {
	INT = 0,
	STRING,
	CARD
};

//this class encapsulates an option and if it needs a parameter and how many
class Option {
public:
	Option();
	~Option() { }
	Option(const Option&) = default;
	Option(Option&&) = default;

	Option& operator=(const Option&) = default;

	bool operator==(const Token& name) const {
		return this->name == name;
	}

	bool operator!=(const Token& name) const {
		return !(*this == name);
	}

	Token name;
	Token descr;

	uint16_t argCount;
	ArgTypes argTypes;
	Arguments arguments;

};

