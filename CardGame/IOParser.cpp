#include "IOParser.h"
#include "CommandFactory.h"

#define IS_OPTION (*it)[0] == '-'

IOParser::IOParser(std::string identifier, Commands&& allCommands) : reader(identifier), commands(allCommands), tokens() {    
    reader.start();
}

IOParser::IOParser() : reader("undef") { }

IOParser::~IOParser() { }

IOParser::IOParser(IOParser&& ioparser) noexcept :  
        reader(std::move(ioparser.reader)) /*moving ioreader shuts it down*/, tokens(std::move(ioparser.tokens)), commands(std::move(ioparser.commands)) {
    
    reader.start(); //start this instances ioreader thread
}

bool IOParser::containsOption(const Options& vect, const Token& opt) {
        for (auto& option : vect)
            if (option == opt) return true;
        return false;
}

bool IOParser::containsOption(const Options& vect, const Option& opt) {
    return containsOption(vect, opt.name);
}

std::string IOParser::HelperPrinter(IOParser& parser) {
    std::ostringstream oss;
    oss << "Known Commands are:\n\n";
    for (auto& c : parser) {
        oss << Command::description(c);
    }

    return oss.str();
}

void IOParser::askInput() {
    reader.read();
    while (reader.isReading());
    Token buffer = reader.getBuffer();
    trim(buffer);
    if (buffer.size() == 0)
        throw CommandException("No command was provided.");
    tokenize(buffer);
    buildAndExecute();
}

void IOParser::trim(std::string& command) {
    if(command.size() == 0) return;
    
    //trim end
    int offs = command.size();
    for (auto it = command.end()-1; it != command.begin() && *it-- == ' '; offs--);
    command = command.substr(0, offs);
    
    //trim front
    offs = 0;
    for (auto it = command.begin(); it != command.end() && *it++ == ' '; offs++);
    command = command.substr(offs, command.size());

    //trim inbetween
    for (auto it = command.begin(); it != command.end()-1;) {
        auto nextChar = it + 1;
        if (*it == ' ' && *it == *nextChar)
            it = command.erase(it);
        else it++;
    }

}

void IOParser::tokenize(Token& buffer) {
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

void IOParser::buildAndExecute() {
    TokenList::iterator it = tokens.begin();

    if (it == tokens.end())
        throw CommandException("No input was provided!");

    //step 1) see if the read command is part of this parser
    Command* ref = 0x0;
    for (auto& c : commands) {
        if (ref) break;
        if (c == (*tokens.begin())) 
            ref = &c;
        
    }

    //throw an exception if the command is not part of the command set
    if (!ref) throw CommandException("The command " + *it + " does not exist!");

    CommandFactory newCommand = CommandFactory().putName(*it++);
    
    //step 2) go through all the provided options (if any) and check if they are correctly parsed (options before parameters, correct amt of parameters for a option)
    //go through all tokens and check for all options and if they come before paramters. also check if options are valid
    for (; it != tokens.end();) {
        //check if an option has been captured
        if (IS_OPTION) {
            Token& optionName = *it++;
            
            //see if the option exists, and if its valid
            const Option& refOption = ref->getOption(optionName); //this will throw an exception which is passed up the call stack
            
            OptionFactory newOption;
            newOption.putName(optionName);

            //this for loop guarantees that the right amount of parameters are captured. if there are not enough
            //or too many options, validation will fail
            for (auto& type : refOption.types) {
                if (it == tokens.end() || IS_OPTION)
                    throw CommandException("The option \"" + refOption.name + "\" takes " + std::to_string(refOption.argCount) + " parameters!");
                
                newOption.addArgument(type, *it++); //try to parse the argument and add it to the factory. throws an exception if parsing fails

            }

            newCommand.putOption(newOption);
        }
        else break;
    }

    //step 3) if all options have been checked, see if rest of tokens have out of place option identifiers or if too many/
    //not enough arguments for command call have been passed
    for (auto& type : ref->argTypes) {
        if (it == tokens.end())
            throw CommandException("The Command \"" + *tokens.begin() + "\" takes " + std::to_string(ref->argCount) + " arguments!");

        if (IS_OPTION)
            throw CommandException("The option identifier \"" + *it + "\" is out of place!");

        newCommand.addArgument(type, *it++); //throws an exception if parsing for this token fails
    }

    if (it != tokens.end())
        throw CommandException("Too many arguments/tokens are provided for Command \"" + *tokens.begin() + "\"!");

    //step 4) if iterator is at the end of the token list, everything should have been parsed correctly and construction and execution of command will begin
    Command cmd = newCommand.finish();

    ref->executor(cmd);
}


