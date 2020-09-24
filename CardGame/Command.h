#pragma once
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include "CommandException.h"

//this macro creates a string from a non-string object
#define STR(name) #name
//this macro makes it easier to define new commands
#define COMMAND(cmd, params) Command cmd(params); \
cmd.name = STR(cmd)

struct Command;
typedef std::string Token;
typedef std::list<Token> TokenList;
typedef std::vector<Token> TokenVector;
typedef std::vector<Command> Commands;

//this class encapsulates an option and if it needs a parameter and how many
struct Option {

	Option(std::string option, uint16_t paramters) : name(option), descr(), b_needsParam(paramters), paramCount(paramters), parameters((int)0) { };
	Option() : name(""), b_needsParam(0), paramCount(0), parameters(0) { };
	Option(const Option& o) = default;
	Option(Option&&) = default;

	Option& operator=(const Option&) = default;

	bool operator==(const std::string& name) const {
		return this->name == name;
	}

	bool operator!=(const std::string& name) const {
		return !(*this == name);
	}

	Token name;
	Token descr;
	bool b_needsParam;
	uint16_t paramCount;
	TokenVector parameters;

};

//this struct holds information about a single command with options and parameters
struct Command {
	typedef std::vector<Option> Options;
	friend class IOParser;

	Command(uint16_t parameters, bool arbitrary = false) : name(), paramCount(parameters), optCount(0), parameters(paramCount), options(optCount), b_allowArbitrary(arbitrary) { };
	Command() : name(""), paramCount(0), optCount(0), parameters(paramCount), options(optCount), b_allowArbitrary(0) { };
	Command(const Command&) = default;
	Command(Command&& cmd) = default;

	Command& operator=(const Command& cmd) = default;
	
	Token name; //name of the command
	Token descr; //description of this command
	uint16_t paramCount; //amount of parameters the command takes
	uint16_t optCount; //amount of options the command takes

	TokenVector parameters; //all parameters
	Options options; //all options


	bool operator==(const std::string& str) const {
		return this->name == str;
	}

	bool operator!=(const std::string& str) const {
		return !(*this == str);
	}

	Option& getOption(const Token& name) {
		for (auto& opt : options)
			if (opt == name) return opt;

		throw CommandException("The option \"" + name + "\" does not exist for this Command!");
	}

	//this helper function creates a formatted description from a command
	static std::string description(const Command& cmd) {
		std::ostringstream oss;
		oss << "\"" << cmd.name << "\":\n";
		//if the command description is too long, make sure some line breaks are added every 20-30 characters or so
		oss << cmd.descr << "\n";

		if (cmd.options.size()) {
			oss << "Options for this Command:\n\n";
			for (auto& opt : cmd.options) {
				oss << "\"" << opt.name << "\": - ";
				oss << opt.descr << "\n";
			}
		}
		
		oss << "---------\n\n";

		return oss.str();
	}

private:
	bool b_allowArbitrary; //whether options can be arbitrary and will not invalidate the command
};
