#pragma once
#include "IOParser.h"
#include "../../IO/IOReader.h"

//this class is the specific implementation for an IOParser that reads from std::in
class CommandParser : public IOParser<IOReader> {
public:

	CommandParser(Token&& identifier, Commands&& allCommands = {}) : IOParser(std::move(identifier), std::move(allCommands)) { };
	CommandParser() : IOParser() { };

	CommandParser(CommandParser&) = delete;
	CommandParser(CommandParser&& instance) noexcept : IOParser(std::move(instance)) { };

	~CommandParser() { };

};

