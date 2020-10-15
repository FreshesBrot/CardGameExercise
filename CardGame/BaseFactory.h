#pragma once
#include "Command.h"
#include "Card.h"

template<typename FacType, typename Storage>
class BaseFactory {
public:
	BaseFactory(FacType* factory) : internal(), factory(factory) { }
	~BaseFactory() { };

	//sets the name for the Storage type
	FacType& putName(const Token&name) {
		internal.name = name;
		return *factory;
	}

	//sets the description for the Storage type
	FacType& putDescription(const Token& descr) {
		internal.descr = descr;
		return *factory;
	}

	//sets the argument types for the Storage type
	FacType& putArguments(ArgTypes&& args) {
		internal.argTypes = args;
		internal.argCount = args.size();

		return *factory;
	}

	//adds an argument to the Storage type
	void addArgument(const ArgType& type, const Token& arg) {
		try {
			switch (type) {
			case ArgType::INT:
				internal.arguments.push_back(new int(std::stoi(arg)));
				break;
			case ArgType::STRING:
				internal.arguments.push_back(new Token(arg));
				break;
			case ArgType::CARD:
				internal.arguments.push_back(new Card(Card::toCard(arg)));
				break;
			}
		} catch (std::exception& e) {
			//honestly this is fkin ugly but it helps to track the exception before it and passing it up the call stack as a different exception
			Token t = Token(e.what());
			throw CommandException(t + "\n" +
				"Command \"" + internal.name + "\" expects an " + ArgAsToken(type) + " as argument nr. " + std::to_string(internal.arguments.size() + 1) +
				" but got \"" + arg + "\"!");
		}
	}

	//finishes and returns Storage type
	Storage finish() {
		return factory->finish();
	}

protected:
	Storage internal; //internal Storage type that will be constructed
	FacType* factory; //keeps track of the factory class instance

	//helper function to parse a argtype into a string
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