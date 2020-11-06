#pragma once
#include "ProtocolHeader.h"

//this struct will contain data that is exchaned between server and client
//struct is templatable on an enumerator
template<typename Type>
struct Protocol {


	ProtocolHeader<Type> header;
};