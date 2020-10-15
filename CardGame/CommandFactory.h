#pragma once
#include "OptionFactory.h"

//forward declarations
class ParserFactory;

//this class makes building commands more easy.
class CommandFactory : public BaseFactory<CommandFactory, Command> {
public:
	friend ParserFactory;

	//Initialize a command factory instance with an empty command
	CommandFactory();
	~CommandFactory();

	//adds a valid option for the command
	CommandFactory& putOption(OptionFactory& option);

	//sets the execution function for the command
	CommandFactory& putFunction(Executor function);
	
	Command finish();

private:
	Options options; //keeps track of all the options

};
