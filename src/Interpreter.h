#pragma once

#include "ISOUtil.h"
#include <iostream>
#include <string>

class Interpreter {
public:
	virtual std::string interpret(std::string data) = 0;
	virtual std::string uninterpret(std::string rawData, int length) = 0;
	virtual int getPackedLength(int nDataUnits) = 0;

protected:
	Interpreter() {};
	virtual ~Interpreter() {};
};
