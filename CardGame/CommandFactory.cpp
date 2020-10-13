#include "CommandFactory.h"
#include "Card.h"

CommandFactory::CommandFactory() : cmd(), options() { }
CommandFactory::~CommandFactory() { };

CommandFactory& CommandFactory::putName(Token name) {
	cmd.name = name;
	return *this;
}

CommandFactory& CommandFactory::putOption(OptionFactory& option) {
	cmd.optCount++;
	options.push_back(option.finish());
	return *this;
}

CommandFactory& CommandFactory::putArguments(ArgTypes arguments) {
	cmd.argTypes = arguments;
	cmd.argCount = arguments.size();
	return *this;
}

CommandFactory& CommandFactory::addArgument(const ArgType& type, Token arg) {
	try {
		switch (type) {
		case ArgType::INT:
				cmd.arguments.push_back(new int(std::stoi(arg)));
			break;
		case ArgType::STRING:
			cmd.arguments.push_back(new Token(arg));
			break;
		case ArgType::CARD:
			cmd.arguments.push_back(new Card(Card::toCard(arg)));
			break;
		}
	} catch (std::exception& e) {
		//honestly this is fkin ugly but it helps to track the exception before it and passing it up the call stack as a different exception
		Token t = Token(e.what());
		throw CommandException(t + "\n" +
			"Command \"" + cmd.name + "\" expects an " + ArgAsToken(type) + " as argument nr. " + std::to_string(cmd.arguments.size() + 1) +
			" but got \"" + arg + "\"!");
	}

	return *this;
}

CommandFactory& CommandFactory::putFunction(Executor function) {
	cmd.executor = std::move(function);
	return *this;
}

CommandFactory& CommandFactory::putDescription(Token* descrPtr) {
	cmd.descr = *descrPtr;
	return *this;
}

Command CommandFactory::finish() {
	cmd.options = options;
	options.clear();
	return cmd;
}

