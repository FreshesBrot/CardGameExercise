#include "IOParser.h"
#define IS_OPTION (*it)[0] == '-'

IOParser::IOParser(std::string identifier) :
                                                        reader(identifier), b_hasCommand(0), b_isCommand(0),
                                                        b_hasParamaters(0), paramCount(0), b_hasOptions(0),
                                                        optCount(0), tokens(0), command(), capturedOptions(0)
{    
    reader.start();
}

IOParser::~IOParser() { }

void IOParser::askInput() {
    reader.read();
    while (reader.isReading());
    Token command = reader.getBuffer();
    tokenize(command);
}

void IOParser::setCommands(std::vector<Command>&& commands) {
    this->commands = commands;
}

Command&& IOParser::getCommand() {
    tokens.clear();
    capturedOptions.clear();
    b_isCommand = false;
    b_hasCommand = false;
    b_hasParamaters = false;
    b_hasParamaters = false;
    paramCount = 0;
    optCount = 0;
    
    return std::move(command);
}

bool IOParser::hasCommand() const {
    return b_hasCommand;
}

bool IOParser::isCommand() const {
    return b_isCommand;
}

bool IOParser::hasParameters() const {
    return b_hasParamaters;
}

uint16_t IOParser::getParameterCount() const {
    return paramCount;
}

bool IOParser::hasOptions() const {
    return b_hasOptions;
}

bool IOParser::containsOption(const Command::Options& vect, const Token& opt) {
        for (auto& option : vect)
            if (option == opt) return true;
        return false;
}

bool IOParser::constainsOption(const Command::Options& vect, const Option& opt) {
    return containsOption(vect, opt.name);
}

void IOParser::trim(std::string& command) {
    int offs = command.size();
    for (auto it = command.end()-1; *it-- == ' '; offs--);
    command = command.substr(0, offs);
}

void IOParser::tokenize(std::string& command) {
    Token buffer;
    tokens.clear();

    trim(command);

    for (auto it = command.begin(); it != command.end(); it++) {
        char c = *it;
        if (c != ' ')
            buffer += c;
        else
            tokens.push_back(Token(std::move(buffer)));
    }

    tokens.push_back(Token(std::move(buffer)));

    b_hasCommand = true;
    validate();

    if(b_isCommand)
        construct();
}

void IOParser::validate() {
    //this function needs to throw a lot of exceptions, so a proper exception system will be required soon

    TokenList::iterator it = tokens.begin();
    
    //step 1) see if the read command is part of this parser
    Command* ref = 0x0;
    for (auto& c : commands) {
        if (ref) break;
        if (c == (*tokens.begin())) {
            ref = &c;
            it++;
        }
    }
    
    if (!ref) return;

    //step 2) go through all the provided options and check if they are correctly parsed (options before parameters, correct amt of parameters for a option)
    //go through all tokens and check for all options and if they come before paramters. also check if options are valid
    for (; it != tokens.end();) {
        //check if an option has been captured
        if (IS_OPTION) {
            Token option = *it;
            it = tokens.erase(it); // to make checking parameters easier, erase the option from the token list

            //if the command allows arbitrary, skip this step and focus on syntax
            if (!ref->b_allowArbitrary) {

                //see if the option exists, and if its valid
                if (containsOption(ref->options, option)) {
                    const Option& refOption = ref->getOption(option);
                    Option newOption(refOption.name, refOption.paramCount);

                    //this for loop guarantees that the right amount of parameters are captured. if there are not enough
                    //or too many options, validation will fail
                    for (int i = 0; i < newOption.paramCount; i++) {
                        if (it == tokens.end() || IS_OPTION) return;
                        newOption.parameters.push_back(*it);
                        //erase the read option parameter from the vector
                        it = tokens.erase(it);
                    }

                    capturedOptions.push_back(newOption);
                } else return;

            } else capturedOptions.push_back(Option(option, 0)); //if arbitrary is active, options will not take parameters
        
        } else break;
    }

    //if all options have been checked, see if rest of tokens have out of place option identifiers or if too many/not enough arguments for command call have been passed
    int count = 0;
    for (; it != tokens.end(); it++) {
        if (IS_OPTION) return;
        count++;
    }

    count *= ref->b_allowArbitrary ^ 0x1;

    if (count != ref->paramCount) return;

    b_isCommand = true;
    optCount = capturedOptions.size();
    b_hasOptions = optCount;
    
    paramCount = tokens.size() - 1;
    b_hasParamaters = paramCount;
}

void IOParser::construct() {
    auto it = tokens.begin();

    command.name = *it++;
    command.optCount = optCount;
    command.paramCount = paramCount;

    if(b_hasOptions)
        for (auto opt : capturedOptions)
            command.options.push_back(opt);

    if(b_hasParamaters)
        for (it; it != tokens.end(); it++)
            command.parameters.push_back(*it);
}
