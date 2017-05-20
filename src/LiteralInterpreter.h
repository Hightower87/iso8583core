#pragma once

#include "Interpreter.h"

class LiteralInterpreter : public Interpreter {
public:
	static Interpreter* INSTANCE;

	std::string interpret(std::string data);
	std::string uninterpret(std::string rawData, int length);
	int getPackedLength(int nDataUnits);

private:
	LiteralInterpreter();
	virtual ~LiteralInterpreter();
};
