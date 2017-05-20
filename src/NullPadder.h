#pragma once

#include "Padder.h"

class NullPadder : public Padder {
public:
	NullPadder(char pad);
	virtual ~NullPadder();

	static Padder* INSTANCE;

	virtual bool pad(std::string& data, int maxLength);
	virtual bool unpad(std::string& paddedData);
};
