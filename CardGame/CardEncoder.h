#pragma once
#include "Card.h"

typedef char byte;

//this class is responsible for encoding card information and storing it in a single byte
class CardEncoder {
public:
	//encodes the given card into a byte
	static byte Encode(const Card& card);
	
private:
	
	CardEncoder() = delete;
	CardEncoder(CardEncoder&) = delete;
	~CardEncoder() {};
};

