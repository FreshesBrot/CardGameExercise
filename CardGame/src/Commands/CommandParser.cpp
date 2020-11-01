#include "CommandParser.h"

CommandParser::CommandParser(Token&& identifier, Commands&& allCommands) : IOParser(this, std::move(identifier), std::move(allCommands)) {

}

void CommandParser::askInput() {
    reader.read();
    while (reader.isReading());

    Token buffer = reader.getBuffer();
    trim(buffer);
    if (buffer.size() == 0)
        throw CommandException("No command was provided.");

    tokenize(buffer);
    buildAndExecute();
}
