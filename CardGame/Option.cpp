#include "Option.h"

Option::Option(std::string option, uint16_t paramters) : name(option), descr(), argCount(paramters), arguments((int)0) { };
Option::Option() : name(""), descr(),argCount(0), types(0), arguments(0) { }

