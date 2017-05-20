#pragma once

#include "Interpreter.h"

class AsciiHexInterpreter : public Interpreter {
public:
	static Interpreter* LEFT_PADDED_0;
	static Interpreter* RIGHT_PADDED_0;
	static Interpreter* LEFT_PADDED_F;
	static Interpreter* RIGHT_PADDED_F;

	std::string interpret(std::string data);
	std::string uninterpret(std::string rawData, int length);
	int getPackedLength(int nDataUnits);

private:
	AsciiHexInterpreter(bool leftPadded, char padchar);
	virtual ~AsciiHexInterpreter();

	bool leftPadded;
	char padchar;
};
