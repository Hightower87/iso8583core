#pragma once
#include "ISOField.h"

class ISOBitMap : public ISOField {
public:
	ISOBitMap();
	virtual ~ISOBitMap();

	bool checkBit(int bitNum);
	void reSetBit(unsigned char bitNum);
	void setBit(unsigned char bitNum);
	void reset();
};

