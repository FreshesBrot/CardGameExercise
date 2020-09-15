#include "IOParser.h"

IOParser::IOParser(std::string identifier) :
                                                        reader(identifier), b_hasCommand(0), b_isCommand(0),
                                                        b_hasParamaters(0), paramCount(0), b_hasOptions(0),
                                                        optCount(0), tokens(0), command() 
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

uint8_t IOParser::getParameterCount() const {
    return paramCount;
}

bool IOParser::hasOptions() const {
    return b_hasOptions;
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

void IOParser::trim(std::string& command) {
    int offs = command.size();
    for (auto it = command.end()-1; *it-- == ' '; offs--);
    command = command.substr(0, offs);
}

void IOParser::validate() {
    Command* ref = 0x0;
    for (auto& c : commands) {
        if (ref) break;
        if (c == tokens[0]) ref = &c;
    }
    
    if (!ref) return;

    Tokens::iterator it;
    Tokens capturedOptions;


    //go through all tokens and check if options come before paramters. also check if options are valid, but dont check parameters
    for (it = ++(tokens.begin()); it != tokens.end();) {
        if ((*it)[0] == '-') capturedOptions.push_back((*it++));
        else break;
    }

    //if all options have been checked, see if rest of tokens have out of place option identifier and if so, return
    for (it; it != tokens.end(); it++) 
        if ((*it)[0] == '-') return;

    //lastly, see if captured options are valid (only if b_allowArbitrary is disabled)
    if (!ref->b_allowArbitrary) {
        for (auto& opt : capturedOptions)
            if (!containsElement(ref->options, opt)) return;
    }
    
    b_isCommand = true;
    optCount = capturedOptions.size();
    b_hasOptions = optCount;
    
    paramCount = tokens.size() - optCount - 1;
    b_hasParamaters = paramCount;
}

void IOParser::construct() {
    auto it = tokens.begin();

    command.name = *it++;
    command.optCount = optCount;
    command.paramCount = paramCount;

    if (b_hasOptions) {
        auto lastIt = it;
        std::advance(it, optCount);
        command.options.insert(command.options.begin(), lastIt, it);
    }
    
    if (b_hasParamaters) {
        auto lastIt = it;
        std::advance(it, paramCount);
        command.parameters.insert(command.parameters.begin(), lastIt, it);
    }
    

}
