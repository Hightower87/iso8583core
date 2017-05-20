#pragma once

#include <string>

class ISOFooter {
public:
	virtual ~ISOFooter();
	ISOFooter();
	virtual std::string pack();
	virtual int unpack(std::string footer);
	virtual int getLength();
	virtual std::string getFooter();
	int GetCrc32(const std::string& data);

protected:
	std::string footer;
};

