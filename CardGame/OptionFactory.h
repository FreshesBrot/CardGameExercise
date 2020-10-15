#pragma once
#include "BaseFactory.h"

//forward declarations
class CommandFactory;

//this class makes building options more easy
class OptionFactory : public BaseFactory<OptionFactory, Option> {
public:
	friend CommandFactory;
	
	OptionFactory();
	~OptionFactory();

	Option finish();

private:
	Option option; //internal option
};
