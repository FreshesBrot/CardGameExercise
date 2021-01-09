#include "CommandParserFactory.h"

CommandParserFactory::CommandParserFactory(uint32_t reserve) : commands() { 
	commands.reserve(reserve);
}

CommandParserFactory::~CommandParserFactory() { }

CommandParserFactory& CommandParserFactory::putName(Token&& name) {
	parserName = name;
	return *this;
}

CommandParserFactory& CommandParserFactory::putCommand(CommandFactory& command) {
	commands.push_back(command.finish());

	return *this;
}

CommandParser CommandParserFactory::finish() {
	CommandParser newParser(std::move(parserName), std::move(commands));

	return newParser; //this thing causes a move error, investigate later
}
