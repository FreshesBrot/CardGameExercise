#pragma once
#include "Card.h"

typedef char byte;

//this class is responsible for decoding card information
class CardDecoder {
public:
	//decode a byte that holds card information
	static Card Decode(byte code);
	

private:
	CardDecoder() = delete;
	CardDecoder(CardDecoder&) = delete;
	~CardDecoder() {};
};

