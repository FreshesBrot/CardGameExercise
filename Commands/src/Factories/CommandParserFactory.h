#pragma once
#include "../Parsing/CommandParser.h"

//this class makes building CommandParser more easy
class CommandParserFactory {
public:
	//initiates an empty factory instance
	CommandParserFactory(uint32_t reserve = 1);
	~CommandParserFactory();

	//declare the name of the IOParser
	CommandParserFactory& putName(Token&& name);

	//add a command to the IOParser
	CommandParserFactory& putCommand(CommandFactory& command);

	CommandParser finish();

private:
	Token parserName; //the name of the parser that will be returned
	Commands commands; //internally stored commands
};
