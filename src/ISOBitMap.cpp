#include "ISOBitMap.h"
#include <stdio.h>

#define ISO8583_BITMAP_INITVALUE 	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

ISOBitMap::ISOBitMap() : ISOField(1, std::string(ISO8583_BITMAP_INITVALUE, 16)) {}
ISOBitMap::~ISOBitMap() {}

bool ISOBitMap::checkBit(int bitNum) {
	std::string bitmap = getValue();
	bitNum--;  // make zero based
	if(bitmap[ bitNum >> 3 ] & (0x01 << (7 - (bitNum % 8)))) {
		setValue(bitmap);
		return true;
	}
	return false;
}

void ISOBitMap::reSetBit(unsigned char bitNum) {
	std::string bitmap = getValue();
	bitNum--; // make zero based
	bitmap[ bitNum >> 3 ] &= ~(0x01 << (7 - (bitNum % 8)));
	setValue(bitmap);
}

void ISOBitMap::setBit(unsigned char bitNum) {
	std::string bitmap = getValue();
	bitNum--; // make zero based
	bitmap[ bitNum >> 3 ] |= (0x01 << (7 - (bitNum % 8)));
	setValue(bitmap);
}

void ISOBitMap::reset() {
	std::string bitmap = std::string(ISO8583_BITMAP_INITVALUE, 16);
	setValue(bitmap);
}

