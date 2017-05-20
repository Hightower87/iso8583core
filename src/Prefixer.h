#pragma once

#include <string>

class Prefixer {
public:
	virtual std::string encodeLength(int length) = 0;
	virtual int decodeLength(std::string& b, int offset = 0) = 0;
	virtual int getPackedLength() = 0;

protected:
	Prefixer(int nDigits) : nDigits(nDigits) {};
    virtual ~Prefixer() {};

    int nDigits;
};
