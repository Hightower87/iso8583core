#pragma once

#include <string>
class ISOField;

class ISOFieldPackagerBase {
public:
	ISOFieldPackagerBase();
	ISOFieldPackagerBase(int len, std::string description);
	virtual ~ISOFieldPackagerBase();
	virtual std::string getDescription();
	virtual void setDescription(std::string description);
	virtual int getLength();
	virtual void setLength(int len);
	virtual ISOField* createComponent(int fldno);
	virtual ISOField* createComponent(int fldno, std::string value);
    virtual int getMaxPackedLength() = 0;
    virtual std::string pack (ISOField* c) = 0;
    virtual int unpack (ISOField* c, std::string b, int offset) = 0;

private:
     int len;
     std::string description;
};

