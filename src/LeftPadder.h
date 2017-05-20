#pragma once

#include "Padder.h"

class LeftPadder : public Padder {
public:
	LeftPadder(char pad);
	virtual ~LeftPadder();

	static Padder* SPACE_PADDER;
	static Padder* ZERO_PADDER;

	virtual bool pad(std::string& data, int maxLength);
	virtual bool unpad(std::string& paddedData);
};
