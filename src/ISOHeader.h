#pragma once

#include <string>

class ISOHeader {
public:
	virtual ~ISOHeader();
	ISOHeader();
	virtual std::string pack();
	virtual int unpack(std::string header);
	virtual int getLength();
	virtual std::string getHeader();

protected:
	std::string header;
};

