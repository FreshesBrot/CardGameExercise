#include "CardEncoder.h"

byte CardEncoder::Encode(Card& card) {
	//first 4 bits hold card number, last 4 bits hold suite
	byte code = 0x00;

	switch (card.getSuite()) {
		case HEARTS:
			code = 0x10;
			break;
		case DIAMONDS:
			code = 0x20;
			break;
		case CLUBS:
			code = 0x30;
			break;
		case SPADES:
			code = 0x40;
			break;
		default:
			return 0x00;
	}

	code += (char)card.getNumber();
	return code;
}
