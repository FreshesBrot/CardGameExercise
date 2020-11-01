#include "ParserFactory.h"

ParserFactory::ParserFactory(uint32_t reserve) : commands() { 
	commands.reserve(reserve);
}
ParserFactory::~ParserFactory() { }

ParserFactory& ParserFactory::putName(Token&& name) {
	parserName = name;
	return *this;
}

ParserFactory& ParserFactory::putCommand(CommandFactory& command) {
	commands.push_back(command.finish());

	return *this;
}

CommandParser ParserFactory::finish() {
	CommandParser newParser(std::move(parserName), std::move(commands));

	return newParser; //this thing causes a move error, investigate later
}
