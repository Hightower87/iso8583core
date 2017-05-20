#pragma once

#include "Prefixer.h"

class BinaryPrefixer : public Prefixer {
public:
	static Prefixer* L;
    static Prefixer* LL;
    static Prefixer* LLL;

    std::string encodeLength(int length);
    int decodeLength(std::string& b, int offset = 0);
    int getPackedLength();

private:
    BinaryPrefixer(int nDigits);
    virtual ~BinaryPrefixer();
};
