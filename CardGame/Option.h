#pragma once
#include <vector>
#include <list>
#include <string>

//forward declarations
enum class ArgType;
class Option;

typedef std::string Token;
typedef std::list<Token> TokenList;
typedef std::vector<Token> TokenVector;
typedef std::vector<void*> Arguments;
typedef std::vector<ArgType> ArgTypes;
typedef std::vector<Option> Options;


//this enumerator is used to classify what argument types are expected
enum class ArgType {
	INT = 0,
	STRING,
	CARD
};

//this class encapsulates an option and if it needs a parameter and how many
class Option {
public:
	Option(std::string option, uint16_t paramters);
	Option();
	~Option() { }
	Option(const Option&) = default;
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

	uint16_t argCount;
	ArgTypes types;
	Arguments arguments;

};

