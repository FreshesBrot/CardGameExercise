#pragma once
#include <vector>
#include <list>
#include <string>

typedef std::string Token;
typedef std::list<Token> TokenList;
typedef std::vector<Token> TokenVector;

//this class encapsulates an option and if it needs a parameter and how many
struct Option {

	Option(std::string option, uint16_t paramters) : name(option), b_needsParam(paramters), paramCount(paramters), parameters((int)0) { };
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
	Command(Command&&) = default;

	Command& operator=(const Command&) = default;

	std::string name; //name of the command
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

		//this is a case where an exception should be thrown! work on that soon 
	}

private:
	bool b_allowArbitrary; //whether options can be arbitrary and will not invalidate the command
};
