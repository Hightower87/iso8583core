#include "BcdInterpreter.h"
#include "ISOUtil.h"

Interpreter* BcdInterpreter::LEFT_PADDED_0 = new BcdInterpreter(true, '0');
Interpreter* BcdInterpreter::RIGHT_PADDED_0 = new BcdInterpreter(false, '0');
Interpreter* BcdInterpreter::RIGHT_PADDED_F = new BcdInterpreter(false, 'F');
Interpreter* BcdInterpreter::LEFT_PADDED_F = new BcdInterpreter(true, 'F');

BcdInterpreter::BcdInterpreter(bool leftPadded, char padchar) : leftPadded(leftPadded), padchar(padchar) {
}

BcdInterpreter::~BcdInterpreter() {
}

std::string BcdInterpreter::interpret(std::string data) {
	std::string b = data;

    unsigned int length = data.length();

    // Make length even and divide by 2
    if (length & 0x01) {
        length++;
    }
    length >>= 1;

    int paddedSize = stringToBCD(b, length, leftPadded);
    if ((data.length()%2) == 1) {
        if (leftPadded) {
    		b[0] &= (unsigned char) 0x0F;
            b[0] |= a2hex(padchar) << 4;
        } else {
    		b[paddedSize - 1] &= (unsigned char) 0xF0;
            b[paddedSize - 1] |= a2hex(padchar);
        }
    }
    return b;
}

std::string BcdInterpreter::uninterpret(std::string rawData, int length) {
	return BCDtostring(rawData, length, leftPadded);
}

int BcdInterpreter::getPackedLength(int nDataUnits) {
	return (nDataUnits + 1) / 2;
}
