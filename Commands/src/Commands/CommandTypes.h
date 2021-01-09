#pragma once
#include <vector>
#include <list>
#include <string>

//forward declarations
enum class ArgType;
class Option;

//useful typedefs
typedef std::string Token;
typedef std::list<Token> TokenList;
typedef std::vector<Token> TokenVector;
typedef std::vector<void*> Arguments;
typedef std::vector<ArgType> ArgTypes;
typedef std::vector<Option> Options;