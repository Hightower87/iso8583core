#pragma once

#include <string>

class ISOField {
public:
	ISOField(int n);
	ISOField(int n, std::string v);
	virtual ~ISOField();
	virtual void setValue(std::string val);
	virtual std::string getValue();
	int getFieldNumber();
	void setFieldNumber(int n);

protected:
	int fieldNumber;
	std::string value;
};
