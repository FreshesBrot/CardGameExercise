#pragma once
#include "IOReader.h"
#include "Command.h"
#include <vector>
#include <list>
#define IO_CONTAINS(elem) IOParser::containsOption(cmd.options, elem)

//an iterator that makes scrolling through all possible commands easier
class CommandIterator {
	typedef Commands::const_iterator __CmdIterator;
public:
	CommandIterator(__CmdIterator iter) : cur(iter) { };
	CommandIterator(const CommandIterator&) = default;
	CommandIterator(CommandIterator&&) = default;
	
	__CmdIterator operator++() {
		return ++cur;
	}

	__CmdIterator operator++(int) {
		__CmdIterator tmp = cur;
		cur++;
		return tmp;
	}

	bool operator==(const CommandIterator& it) const {
		return cur == it.cur;
	}

	bool operator!=(const CommandIterator& it) const {
		return !(*this == it);
	}

	const Command& operator*() {
		return *cur;
	}

	const Command* operator->() {
		return &(*cur);
	}
private:
	__CmdIterator cur;
};

class ParserFactory; //forward declaration

//this class takes the input from the IO reader to convert it into tokens that are turned into a command
class IOParser {
public:
	friend ParserFactory; //make parserfactory to capsulate access to setCommands

	//construct a new io interpreter with a new ioreader thread
	IOParser(std::string identifier, Commands&& alLCommands = { });
	IOParser();
	~IOParser();
	IOParser(const IOParser&&) = delete;
	IOParser(IOParser&& ioparser) noexcept;

	//ask the interpreter to take an input and execute it. this function will throw an exception if parsing fails
	void askInput();

	//iterator beginning to iterate through commands
	CommandIterator begin() {
		return CommandIterator(commands.begin());
	}
	
	CommandIterator end() {
		return CommandIterator(commands.end());
	}

	//helper function to determine if a vector contains a certain element
	static bool containsOption(const Options& vect, const Token& opt);
	static bool containsOption(const Options& vect, const Option& opt);

	//helper function that takes care of printing the helper message
	static std::string HelperPrinter(IOParser& parser);

private:
	void tokenize(Token& buffer);

	//builds the command and executes it.
	void buildAndExecute();
	//trims whitespaces off the end
	void trim(std::string& command);


	IOReader reader; //the ioreader that takes the inputs

	TokenList tokens; //list of all captured tokens
	
	Commands commands; //all commands that are recognized	
};

