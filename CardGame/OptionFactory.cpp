#include "OptionFactory.h"
#include "Card.h"
#include "CommandException.h"
#define STR(x) #x

OptionFactory::OptionFactory() : option() { }
OptionFactory::~OptionFactory() { }

OptionFactory& OptionFactory::putName(Token name) {
	option.name = name;
	return *this;
}

OptionFactory& OptionFactory::putArguments(ArgTypes arguments) {
	option.types = arguments;
	option.argCount = arguments.size();
	return *this;
}

OptionFactory& OptionFactory::addArgument(const ArgType& type, Token arg) {
	try {
		switch (type) {
		case ArgType::INT:
			option.arguments.push_back(new int(std::stoi(arg)));
			break;
		case ArgType::STRING:
			option.arguments.push_back(new Token(arg));
			break;
		case ArgType::CARD:
			option.arguments.push_back(new Card(Card::toCard(arg)));
			break;
		}
	} catch (std::exception& e) {
		Token t = Token(e.what());
		throw CommandException(t + "\n" +
			"Option \"" + option.name + "\" expects an " + ArgAsToken(type) + " as argument nr. " + std::to_string(option.arguments.size() + 1) +
			" but got \"" + arg + "\"!");
	}

	return *this;
}

OptionFactory& OptionFactory::putDescription(Token* descrPtr) {
	option.descr = *descrPtr;
	return *this;
}

Option OptionFactory::finish() {
	return option;
}