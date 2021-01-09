#include "CommandFactory.h"


CommandFactory::CommandFactory() : BaseFactory(this), options() { }
CommandFactory::~CommandFactory() { };

CommandFactory& CommandFactory::putOption(OptionFactory& option) {
	internal.optCount++;
	options.push_back(option.finish());
	return *this;
}

CommandFactory& CommandFactory::putFunction(Executor&& function) {
	internal.executor = function;
	return *this;
}

Command CommandFactory::finish() {
	internal.options = options;
	options.clear();
	return internal;
}

