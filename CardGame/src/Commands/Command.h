#pragma once
#include <sstream>
#include "Option.h"
#include "../Exceptions/CommandException.h"
#include <functional>

class Command;

typedef std::vector<Command> Commands;
typedef std::function<void(Command&)> Executor;
//typedef void (*Executor)(Command&);

//this struct holds information about a single command with options, parameters and their types as well as the executable function of the command
class Command {
public:
	friend class IOParser;

	Command();
	~Command() { } 
	Command(const Command&) = default;
	Command(Command&& cmd) noexcept;

	Command& operator=(const Command& cmd) = default;

	Token name; //name of the command
	Token descr; //description of this command
	uint16_t argCount; //amount of parameters the command takes
	uint16_t optCount; //amount of options the command takes

	ArgTypes argTypes; //all expected argument types
	Arguments arguments; //all parameters
	Options options; //all options
	
	Executor executor; //the function that is executed for this command.

	bool operator==(const Token& str) const {
		return this->name == str;
	}

	bool operator!=(const Token& str) const {
		return !(*this == str);
	}

	Option& getOption(const Token& name);

	//retrieves type cast argument from arguments list
	template<typename Arg>
	static Arg& getArgument(Command& cmd, int where) {
		if (where >= cmd.arguments.size())
			throw CommandException("Tried to access an argument at out of bounds position.");
		
		return *static_cast<Arg*>(cmd.arguments[where]);
	}

	template<typename Arg>
	static Arg& getArgument(Option& opt, int where) {
		if (where >= opt.arguments.size())
			throw CommandException("Tried to access an argument at out of bounds position.");
		
		return *static_cast<Arg*>(opt.arguments[where]);
	}

	//this helper function creates a formatted description from a command
	static std::string description(const Command& cmd);

};
