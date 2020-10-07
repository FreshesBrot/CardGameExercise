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
	switch (type) {
	case ArgType::STRING:
		option.arguments.push_back(new Token(arg));
		break;
	case ArgType::INT:
		try {
			option.arguments.push_back(new int(std::stoi(arg)));
		} catch (std::exception&) {
			throw CommandException("Option \""+option.name+"\" expects an integer as argument nr. " + std::to_string(option.arguments.size()+1) + " but got \""+arg+"\"!");
		}
		break;
	case ArgType::CARD:
		option.arguments.push_back(new Card(Card::toCard(arg)));
		break;
	}

	option.argCount++;

	return *this;
}

OptionFactory& OptionFactory::putDescription(Token* descrPtr) {
	option.descr = *descrPtr;
	return *this;
}

Option OptionFactory::finish() {
	return option;
}