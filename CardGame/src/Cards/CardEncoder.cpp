#include "CardEncoder.h"

byte CardEncoder::Encode(const Card& card) {
	//first 4 bits hold card number, last 4 bits hold suite
	byte code = 0x00;

	switch (card.getSuite()) {
	case Suite::HEARTS:
			code = 0x10;
			break;
	case Suite::DIAMONDS:
			code = 0x20;
			break;
	case Suite::CLUBS:
			code = 0x30;
			break;
	case Suite::SPADES:
			code = 0x40;
			break;
	default:
			return 0x00;
	}

	code += (uint8_t)card.getNumber();
	return code;
}
