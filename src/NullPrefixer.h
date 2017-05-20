#pragma once

#include "Prefixer.h"

class NullPrefixer  : public Prefixer {
public:
	static Prefixer* INSTANCE;

    std::string encodeLength(int length);
    int decodeLength(std::string& b, int offset = 0);
    int getPackedLength();

private:
    NullPrefixer();
    virtual ~NullPrefixer();
};
