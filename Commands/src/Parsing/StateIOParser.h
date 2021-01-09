#pragma once
#include "IOParser.h"
#include <unordered_map>


//the state parser supports multiple command vectors templated on a state enum
template <typename States,  typename IOStream>
class StateIOParser : public IOParser<IOStream> {
public:
	typedef std::unordered_map<States, Commands> StateMap;

	StateIOParser(Token&& identifier, StateMap&& map = { }) : IOParser<IOStream>(std::move(identifier)), allCommands(std::move(map)) { }
	StateIOParser() : IOParser<IOStream>() { }

	StateIOParser(StateIOParser&) = delete;
	StateIOParser(StateIOParser&& parser) noexcept : IOParser<IOStream>() {
		*this = std::move(parser);
	}

	StateIOParser& operator=(StateIOParser&& parser) noexcept {
		if (this == &parser) return *this;
		IOParser<IOStream>::operator=(std::move(parser));
		allCommands.clear();
		allCommands = std::move(parser.allCommands);
		std::swap(curState, parser.curState);

		return *this;
	}

	//changes the set of commands that will be executed according to the state
	void changeState(States state) {
		curState = state;
	}

	void askInput() override {
		this->reader.read();
		while (this->reader.isReading());

		Token buffer = this->reader.getBuffer();
		this->trim(buffer);
		if (buffer.size() == 0)
			throw CommandException("No command was provided.");

		this->tokenize(buffer);
		this->buildAndExecute();
	}

	Token getHelperMessage() override {
		return this->constructHelperMessage(allCommands[curState]);
	}

protected:

	//build the command from the parsed input tokens and execute if possible
	void buildAndExecute() override {
		//for documentation check parent class implementation
		TokenList::iterator it = this->tokens.begin();

		if (it == this->tokens.end())
			throw CommandException("No input was provided!");

		Command* ref = commandExists(it);

		CommandFactory newCommand = CommandFactory().putName(std::move(*it++));

		this->validateOptions(it, ref, newCommand);

		this->validateArguments(it, ref, newCommand);

		if (it != this->tokens.end())
			throw CommandException("Too many arguments/tokens are provided for Command \"" + *this->tokens.begin() + "\"!");

		Command cmd = newCommand.finish();

		ref->executor(cmd);
	}

	//new implementation for commandExists that supports multiple managed states
	inline Command* commandExists(TokenList::iterator& it) {
		Command* ref = 0x0;
		//active commands are chosen depending on the current state of the state parser
		Commands& activeCommands = allCommands[curState];

		for (auto& c : activeCommands) {
			if (ref) break;
			if (c == (*this->tokens.begin()))
				ref = &c;

		}

		//throw an exception if the command is not part of the command set
		if (!ref) throw CommandException("The command " + *it + " does not exist!");

		return ref;
	}

	States curState;
	StateMap allCommands;

};

