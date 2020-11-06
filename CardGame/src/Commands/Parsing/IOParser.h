#pragma once
#include "../CommandFactory.h"
#include <iostream>

#define IO_CONTAINS(elem) IOParser::containsOption(cmd.options, elem)
#define IS_OPTION (*it)[0] == '-'


//this class is the base class for parsers that read from an IOStream input stream and convert it into a tokenized command form
template<typename IOStream>
class IOParser {
public:

	//construct a new io interpreter with a new ioreader thread
	IOParser(Token&& identifier, Commands&& allCommands = { }) : reader(std::move(identifier)), commands(allCommands), tokens(), b_suspended(false) {
		reader.start();
	};

	//stand-in standard constructor - might not be needed eventually
	IOParser() { };

	~IOParser() { };
	
	//class is not copyable
	IOParser(const IOParser&) = delete;
	
	//class is however moveable. uses move assignment to move resources, looks cleaner and better
	IOParser(IOParser&& parser) noexcept : 
		reader(), tokens(), commands(), b_suspended(false) {

		*this = std::move(parser);
	}

	//move assignment operator. handles everything to move resources from the rhs parser to the assigned parser
	IOParser& operator=(IOParser&& parser) noexcept {
		if (this == &parser) return *this;
		reader.shutdown();
		commands.clear();
		tokens.clear();
		
		reader = std::move(parser.reader);
		commands = std::move(parser.commands);
		tokens = std::move(parser.tokens);
		b_suspended = parser.b_suspended;

		return *this;
	}

	virtual void askInput() {
		reader.read();
		while (reader.isReading());

		Token buffer = reader.getBuffer();
		trim(buffer);
		if (buffer.size() == 0)
			throw CommandException("No command was provided.");

		tokenize(buffer);
		buildAndExecute();
	}

	//suspends this parser from waiting for input
	void suspend() {
		if (!b_suspended) {
			b_suspended = true;
			reader.shutdown();
		}
	}

	//restarts the parser after it has been suspended
	void restart() {
		if (b_suspended) {
			b_suspended = false;
			reader.start();
		}
	}

	//returns whether this IOReader is currently inactive or not
	bool isSuspended() const {
		return b_suspended;
	}

	//helper function to determine if a vector contains a certain element
	static bool containsOption(const Options& vect, const Token& opt) {
		for (auto& option : vect)
			if (option == opt) return true;
		return false;
	}

	static bool containsOption(const Options& vect, const Option& opt) {
		return containsOption(vect, opt.name);
	}

	//helper function that takes care of printing the helper message
	virtual Token getHelperMessage() {
		return constructHelperMessage(commands);
	}


protected:
	IOStream reader; //the ioreader that takes the inputs
	TokenList tokens; //list of all captured tokens
	Commands commands; //all commands that are recognized	
	bool b_suspended; //whether this IOReader is currently not active or not

	//internal implementation of getHelperMessage 
	Token constructHelperMessage(Commands& cmds) {
		std::ostringstream oss;
		oss << "Known Commands are:\n\n";
		for (auto& c : cmds) {
			oss << Command::description(c);
		}

		return oss.str();
	}

	//tokenizes the input from the IOReader into managable tokens
	void tokenize(Token& buffer) {
		tokens.clear();
		Token next;

		for (auto c : buffer) {
			if (c != ' ')
				next += c;
			else {
				tokens.push_back(next);
				next.clear();
				continue;
			}
		}
		tokens.push_back(next);
	}

	//builds the command and executes it.
	virtual void buildAndExecute() {
		TokenList::iterator it = tokens.begin();

		if (it == tokens.end())
			throw CommandException("No input was provided!");

		//step 1) see if the read command is part of this parser
		Command* ref = commandExists(it);

		CommandFactory newCommand = CommandFactory().putName(std::move(*it++));

		//step 2) go through all the provided options (if any) and check if they are correctly parsed (options before parameters, correct amt of parameters for a option)
		//go through all tokens and check for all options and if they come before paramters. also check if options are valid
		validateOptions(it, ref, newCommand);

		//step 3) if all options have been checked, see if rest of tokens have out of place option identifiers or if too many/
		//not enough arguments for command call have been passed
		validateArguments(it, ref, newCommand);

		if (it != tokens.end())
			throw CommandException("Too many arguments/tokens are provided for Command \"" + *tokens.begin() + "\"!");

		//step 4) if iterator is at the end of the token list, everything should have been parsed correctly and construction and execution of command will begin
		Command cmd = newCommand.finish();

		ref->executor(cmd);
	}

	//trims whitespaces off the end
	void trim(Token& buffer) {
		if (buffer.size() == 0) return;

		//trim end
		int offs = buffer.size();
		for (auto it = buffer.end() - 1; it != buffer.begin() && *it-- == ' '; offs--);
		buffer = buffer.substr(0, offs);

		//trim front
		offs = 0;
		for (auto it = buffer.begin(); it != buffer.end() && *it++ == ' '; offs++);
		buffer = buffer.substr(offs, buffer.size());

		//trim inbetween
		for (auto it = buffer.begin(); it != buffer.end() - 1;) {
			auto nextChar = it + 1;
			if (*it == ' ' && *it == *nextChar)
				it = buffer.erase(it);
			else it++;
		}

	}

	
#pragma region HelperFunctions
	//step 1 for the tokenizer
	inline Command* commandExists(TokenList::iterator& it) {
		Command* ref = 0x0;
		for (auto& c : commands) {
			if (ref) break;
			if (c == (*tokens.begin()))
				ref = &c;

		}

		//throw an exception if the command is not part of the command set
		if (!ref) throw CommandException("The command " + *it + " does not exist!");

		return ref;
	}

	//step 2 for the tokenizer
	inline void validateOptions(TokenList::iterator& it, Command* ref, CommandFactory& newCommand) {
		for (; it != tokens.end();) {
			//check if an option has been captured
			if (IS_OPTION) {
				Token& optionName = *it++;

				//see if the option exists, and if its valid
				const Option& refOption = ref->getOption(optionName); //this will throw an exception which is passed up the call stack

				OptionFactory newOption;
				newOption.putName(std::move(optionName));

				//this for loop guarantees that the right amount of parameters are captured. if there are not enough
				//or too many options, validation will fail
				for (auto& type : refOption.argTypes) {
					if (it == tokens.end() || IS_OPTION)
						throw CommandException("The option \"" + refOption.name + "\" takes " + std::to_string(refOption.argCount) + " parameters!");

					newOption.addArgument(type, *it++); //try to parse the argument and add it to the factory. throws an exception if parsing fails

				}

				newCommand.putOption(newOption);
			}
			else break;
		}
	}

	//step 3 for the tokenizer
	inline void validateArguments(TokenList::iterator& it, Command* ref, CommandFactory& newCommand) {
		for (auto& type : ref->argTypes) {
			if (it == tokens.end())
				throw CommandException("The Command \"" + newCommand.getName() + "\" takes " + std::to_string(ref->argCount) + " arguments!");

			if (IS_OPTION)
				throw CommandException("The option identifier \"" + *it + "\" is out of place!");

			newCommand.addArgument(type, *it++); //throws an exception if parsing for this token fails
		}

		if (it != tokens.end())
			throw CommandException("Too many arguments/tokens are provided for Command \"" + *tokens.begin() + "\"!");
	}

#pragma endregion
};

