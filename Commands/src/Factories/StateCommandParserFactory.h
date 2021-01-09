#pragma once
#include "../Parsing/StateCommandParser.h"

//this class makes creating state parsers easier
template<typename States>
class StateCommandParserFactory {
public:
	typedef StateCommandParser<States> SCP;
	typedef StateCommandParserFactory<States> SPF;
	typedef std::unordered_map<States, Commands> StateMap;

	StateCommandParserFactory(std::vector<States>&& allStates) : allCommands(), parserName() {
		for (auto& c : allStates) {
			allCommands[c] = Commands();
		}
	}

	~StateCommandParserFactory() { }

	SPF putName(Token&& name) {
		parserName = std::move(name);
		return *this;
	}

	SPF putCommand(States state, CommandFactory& command) {
		allCommands[state].push_back(command.finish());
		
		return *this;
	}

	SCP finish() {
		SCP newParser(std::move(parserName), std::move(allCommands));

		return newParser;
	}

private:
	Token parserName;
	std::unordered_map<States, Commands> allCommands;
};