#pragma once
#include "IOParser.h"
#include "../IO/IOReader.h"

//this class is the specific implementation for an IOParser that reads from std::in
class CommandParser : public IOParser<IOReader, CommandParser> {
public:

	CommandParser(Token&& identifier, Commands&& allCommands = {});
	CommandParser() : IOParser() { };
	CommandParser(CommandParser&& instance) noexcept : IOParser(std::move(instance)) { };

	~CommandParser() { };

	//make IOParser friend of this class so it can access this implementation of askInput
	void askInput();
};

