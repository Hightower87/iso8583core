#pragma once
#include <string>

#include "ISOFieldPackagerBase.h"
class ISOField;

class ISOBitMapPackager : public ISOFieldPackagerBase {
public:
	ISOBitMapPackager();
	ISOBitMapPackager(int len, std::string description);
	virtual ~ISOBitMapPackager();

	virtual ISOField* createComponent(int fieldNumber);
	int getMaxPackedLength();
    virtual std::string pack (ISOField* c);
    virtual int unpack (ISOField* c, std::string b, int offset);
};

