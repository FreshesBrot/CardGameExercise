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
	return *this;
}

CommandFactory& CommandFactory::addArgument(const ArgType& type, Token arg) {
	switch (type) {
	case ArgType::STRING:
		cmd.arguments.push_back(new Token(arg));
		break;
	case ArgType::INT:
		try {
			cmd.arguments.push_back(new int(std::stoi(arg)));
		}
		catch (std::exception&) {
			throw CommandException("Command \"" + cmd.name + "\" expects an integer as argument nr. " + std::to_string(cmd.arguments.size() + 1) + " but got \"" + arg +"\"!");
		}
		break;
	case ArgType::CARD:
		cmd.arguments.push_back(new Card(Card::toCard(arg)));
		break;
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

