#pragma once
#include "CommandFactory.h"
#include "CommandParser.h"

//this class makes building IOParser more easy
class ParserFactory {
public:
	//initiates an empty factory instance
	ParserFactory(uint32_t reserve = 1);
	~ParserFactory();

	//declare the name of the IOParser
	ParserFactory& putName(Token&& name);

	//add a command to the IOParser
	ParserFactory& putCommand(CommandFactory& command);

	CommandParser finish();

private:
	Token parserName; //the name of the parser that will be returned
	Commands commands; //internally stored commands
};
