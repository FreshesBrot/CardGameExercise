#include "CardDecoder.h"

Card CardDecoder::Decode(byte code) {
	//first 4 bits hold card number, last 4 bits hold suite
	byte suite = (code & 0xf0) >> 4;
	byte number = (code & 0x0f);

	return Card(Suite(suite), number);
}
