#pragma once
#include "IOReader.h"
#include "Command.h"
#include <vector>
#include <list>

//this class takes the input from the IO reader to convert it into tokens that are turned into a command
class IOParser {
public:

	//construct a new io interpreter with a new ioreader thread
	IOParser(std::string identifier);
	~IOParser();
	IOParser(const IOParser&&) = delete;
	IOParser(IOParser&&) = delete;

	//ask the interpreter to take an input
	void askInput();
	
	//set the list of commands the interperter can recognize
	void setCommands(std::vector<Command>&&);
	
	//retrieves the command that has been interpreted, if the command is valid. clears all buffers as well
	Command&& getCommand();

	//returns a reference to the tokens
	inline const TokenList& getTokens() const { return tokens; };

	//returns true if the interpreter has a command stored
	bool hasCommand() const;
	//returns true if the interpreted input was a valid command
	bool isCommand() const;
	//returns true if the command has additional paramters
	bool hasParameters() const;
	//returns how many parameters are expected from the read command
	uint16_t getParameterCount() const;
	//returns true if the command has any options
	bool hasOptions() const;

	
	//helper function to determine if a vector contains a certain element
	static bool containsOption(const Command::Options& vect, const Token& opt);
	static bool constainsOption(const Command::Options& vect, const Option& opt);

private:
	//takes the IO buffer and converts it into tokens. calling tokenize clears the previous tokens buffer
	void tokenize(std::string& command); 
	//trims whitespaces off the end
	void trim(std::string& command);
	//checks the current tokens if they are a valid command that can be used. sets several flags that determine state of the interpreter
	void validate();
	//constructs the command from the tokens
	void construct();

	IOReader reader; //the ioreader that takes the inputs

	//flags that hold information about the IO interpreters interpreted command
	bool b_hasCommand; //if this interpeter has a command or not
	bool b_isCommand; //if the read input is a valid command
	bool b_hasParamaters; //if the command has any parameters
	uint16_t paramCount; //how many parameters are read from the command
	bool b_hasOptions; //if the command has any options
	uint16_t optCount; //how many options are read from the command
	Command::Options capturedOptions; // all captured options

	TokenList tokens; //tokenized command string
	Command command; //internally constructed command

	std::vector<Command> commands; //all commands that are recognized	
};

