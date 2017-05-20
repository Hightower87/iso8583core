#include "LiteralInterpreter.h"

Interpreter* LiteralInterpreter::INSTANCE = new LiteralInterpreter();

LiteralInterpreter::LiteralInterpreter() {
}

LiteralInterpreter::~LiteralInterpreter() {
}

std::string LiteralInterpreter::interpret(std::string data) {
    return data;
}

std::string LiteralInterpreter::uninterpret(std::string rawData, int length) {
	return rawData;
}

int LiteralInterpreter::getPackedLength(int nDataUnits) {
	return nDataUnits;
}
