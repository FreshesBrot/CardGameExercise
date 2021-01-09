#include "OptionFactory.h"

OptionFactory::OptionFactory() : BaseFactory(this) { }
OptionFactory::~OptionFactory() { }

Option OptionFactory::finish() {
	return internal;
}
