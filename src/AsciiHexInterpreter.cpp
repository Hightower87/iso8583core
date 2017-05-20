#include "AsciiHexInterpreter.h"

Interpreter* AsciiHexInterpreter::LEFT_PADDED_0 = new AsciiHexInterpreter(true, '0');
Interpreter* AsciiHexInterpreter::RIGHT_PADDED_0 = new AsciiHexInterpreter(false, '0');
Interpreter* AsciiHexInterpreter::LEFT_PADDED_F = new AsciiHexInterpreter(true, 'F');
Interpreter* AsciiHexInterpreter::RIGHT_PADDED_F = new AsciiHexInterpreter(false, 'F');

AsciiHexInterpreter::AsciiHexInterpreter(bool leftPadded, char padchar) : leftPadded(leftPadded), padchar(padchar) {
}

AsciiHexInterpreter::~AsciiHexInterpreter() {
}

std::string AsciiHexInterpreter::interpret(std::string data) {
    size_t len = data.length();
    if (len & 1) {
        if(leftPadded) {
			data.insert(0, 1, padchar);
        } else {
			data += padchar;
        }
    }
    return asciiToHex(data);
}

std::string AsciiHexInterpreter::uninterpret(std::string rawData, int length) {
	std::string output = hexToAscii(rawData);
	if((length & 1) && output.size() > (unsigned int)length) {
		if (leftPadded && output[0] == padchar) {
			output.erase(0, 1);
		} else if (!leftPadded && output[output.size() - 1] == padchar) {
			output.erase(output.size() - 1);
		}
	}
	return output;
}

int AsciiHexInterpreter::getPackedLength(int nDataUnits) {
	return (nDataUnits + 1) / 2;
}
