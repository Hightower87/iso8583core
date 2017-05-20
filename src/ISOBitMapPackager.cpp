#include "ISOBitMapPackager.h"
#include "ISOBitMap.h"
#include "ISOField.h"

ISOBitMapPackager::ISOBitMapPackager() {}
ISOBitMapPackager::ISOBitMapPackager(int len, std::string description) : ISOFieldPackagerBase(len, description) {}
ISOBitMapPackager::~ISOBitMapPackager() {}

ISOField* ISOBitMapPackager::createComponent(int fieldNumber) {
	return new ISOBitMap();
}

int ISOBitMapPackager::getMaxPackedLength() {
	return getLength() >> 3;
}

std::string ISOBitMapPackager::pack (ISOField* c) {
	ISOBitMap* bitmap = dynamic_cast<ISOBitMap*>(c);
	if(c == NULL) {
		return "";
	}

	bool secondary = false;
	for (int i=64; i<=128; i++) {	//check if secondary bitmap shall be defined
		if(bitmap->checkBit(i)) {
			secondary = true;
			break;
		}
	}

	std::string s_bitmap = bitmap->getValue();
	if(secondary) {
		s_bitmap[0] |= 0x80;
	} else {
		s_bitmap = s_bitmap.substr(0, 8);
	}

    return s_bitmap;
}

int ISOBitMapPackager::unpack(ISOField* c, std::string b, int offset) {
	std::string s_bitmap = "";
	if(b[offset] & 0x80) {
		s_bitmap = b.substr(offset, 16);
	} else {
		s_bitmap = b.substr(offset, 8);
	}
	c->setValue(s_bitmap);
	return s_bitmap.size();
}

