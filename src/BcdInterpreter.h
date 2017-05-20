#pragma once

#include "Interpreter.h"

class BcdInterpreter : public Interpreter {
public:
    static Interpreter* LEFT_PADDED_0;
    static Interpreter* RIGHT_PADDED_0;
    static Interpreter* RIGHT_PADDED_F;
    static Interpreter* LEFT_PADDED_F;

    std::string interpret(std::string data);
	std::string uninterpret(std::string rawData, int length);
	int getPackedLength(int nDataUnits);

private:
	BcdInterpreter(bool leftPadded, char padchar);
	virtual ~BcdInterpreter();

	bool leftPadded;
	char padchar;
};
