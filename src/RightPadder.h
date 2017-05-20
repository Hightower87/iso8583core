#pragma once

#include "Padder.h"

class RightPadder : public Padder {
public:
	RightPadder(char pad);
	virtual ~RightPadder();

	static Padder* SPACE_PADDER;
	static Padder* ZERO_PADDER;

	virtual bool pad(std::string& data, int maxLength);
	virtual bool unpad(std::string& paddedData);
};

