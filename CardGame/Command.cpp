#include "Command.h"

Command::Command() : name(""), descr(), argCount(0), optCount(0), argTypes(0), arguments(0), options(0), executor(nullptr) { }

Command::Command(Command&& cmd) :
	name(std::move(cmd.name)), descr(std::move(cmd.descr)), argCount(cmd.argCount), argTypes(std::move(cmd.argTypes)),
	arguments(std::move(cmd.arguments)), options(std::move(cmd.options)) {
	
	this->executor = cmd.executor;
	cmd.executor = nullptr;
}

Option& Command::getOption(const Token& name) {
	for (auto& opt : options)
		if (opt == name) return opt;

	throw CommandException("The option \"" + name + "\" does not exist for the Command \""+this->name+"\"!");
}

std::string Command::description(const Command& cmd) {
	std::ostringstream oss;
	oss << "\"" << cmd.name << "\":\n";
	//if the command description is too long, make sure some line breaks are added every 20-30 characters or so
	oss << cmd.descr << "\n";

	if (cmd.options.size()) {
		oss << "Options for this Command:\n\n";
		for (auto& opt : cmd.options) {
			oss << "\"" << opt.name << "\": - ";
			oss << opt.descr << "\n";
		}
	}

	oss << "---------\n\n";

	return oss.str();
}