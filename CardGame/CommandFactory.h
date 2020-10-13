#pragma once
#include "OptionFactory.h"
#include "Command.h"

//TODO; idea could be to make a IOParser factory and have it use the command factory in a similar way the command factory uses the options factory. makes it even easier to create commands

class ParserFactory;
/*
	new idea: make factories inherit from a template base class, where
	template <typename Return, typename Storage>
	class BaseFactory {
	public:
		Return& putName() {
		
		}
		.
		.
		Storage finish() {
		
		}
	private:
		Storage storage;
	}

	class OptionFactory : BaseFactory<OptionFactory, Option>

	probably need to refactor commands and options to be related as inheritance classes to make some tricks work...
*/

//this class makes building commands more easy.
class CommandFactory {
public:

	//Initialize a command factory instance with an empty command
	CommandFactory();
	~CommandFactory();

	//sets the name for the command
	CommandFactory& putName(Token name);

	//adds a valid option for the command
	CommandFactory& putOption(OptionFactory& option);

	//sets expected arguments for the command
	CommandFactory& putArguments(ArgTypes arguments);

	//will try to parse the argument into the proper type and add it to the command. this class will throw an exception if parsing fails
	CommandFactory& addArgument(const ArgType& type, Token arg);

	//sets the execution function for the command
	CommandFactory& putFunction(Executor function);

	//sets the commands description. 
	CommandFactory& putDescription(Token* descrPtr);

	//constructs a command and moves it. command will be empty afterwards
	Command finish();
	
private:
	Command cmd; //the command that is being worked on
	Options options; //keeps track of all the options

	//helper function, not important
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
