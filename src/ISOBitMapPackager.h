#pragma once
#include <string>

#include "ISOFieldPackagerBase.h"
class ISOField;

class ISOBitMapPackager : public ISOFieldPackagerBase {
public:
	ISOBitMapPackager();
	ISOBitMapPackager(int len, std::string description);
	virtual ~ISOBitMapPackager();

	virtual boost::shared_ptr<ISOField> createComponent(int fieldNumber);
	int getMaxPackedLength();
    virtual std::string pack (boost::shared_ptr<ISOField> c);
    virtual int unpack (boost::shared_ptr<ISOField> c, std::string b, int offset);
};

