#include "OptionFactory.h"
#include "Card.h"
#include "CommandException.h"
#define STR(x) #x

OptionFactory::OptionFactory() : BaseFactory(this) { }
OptionFactory::~OptionFactory() { }

Option OptionFactory::finish() {
	return internal;
}
