#pragma once
#include "Option.h"

class CommandFactory; //simple forward declaration

//this class makes building options more easy
class OptionFactory {
public:
	friend CommandFactory;

	OptionFactory();
	~OptionFactory();

	//sets the name for this option
	OptionFactory& putName(Token name);

	//sets the argument types (And num of args) for this option
	OptionFactory& putArguments(ArgTypes arguments);

	//adds an argument to this option (used during command parsing). throws an exception if parsing fails
	OptionFactory& addArgument(const ArgType& type, Token arg);

	//sets the description for this option
	OptionFactory& putDescription(Token* descrPtr);

private:
	Option finish(); //called by CommandFactory once option is done
	Option option; //internal option

	//helper function
	inline static Token ArgAsToken(const ArgType& arg) {
		switch (arg) {
		case ArgType::STRING:
			return "string";
		case ArgType::INT:
			return "integer";
		case ArgType::CARD:
			return "card";
		}
	}

};
