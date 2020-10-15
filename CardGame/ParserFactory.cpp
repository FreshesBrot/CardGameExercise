#include "ParserFactory.h"

ParserFactory::ParserFactory(uint32_t reserve) : commands() { 
	commands.reserve(reserve);
}
ParserFactory::~ParserFactory() { }

ParserFactory& ParserFactory::putName(const Token& name) {
	this->parserName = name;
	return *this;
}

ParserFactory& ParserFactory::putCommand(CommandFactory& command) {
	commands.push_back(command.finish());

	return *this;
}

IOParser ParserFactory::finish() {
	IOParser newParser(parserName,std::move(commands));

	return newParser; //this thing causes a move error, investigate later
}
