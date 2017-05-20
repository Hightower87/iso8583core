#include "LeftPadder.h"
#include <iostream>

Padder* LeftPadder::SPACE_PADDER = new LeftPadder(' ');
Padder* LeftPadder::ZERO_PADDER = new LeftPadder('0');

LeftPadder::LeftPadder(char pad) : Padder(pad) {
}

LeftPadder::~LeftPadder() {
}

bool LeftPadder::pad(std::string& data, int maxLength) {
    int len = data.length();
    if (len > maxLength) {
        return false;
    } else {
        for (int i = maxLength - len; i > 0; i--) {
        	data.insert(0, std::string(1, pad_char));
        }
    }
    return true;
}

bool LeftPadder::unpad(std::string& paddedData) {
	unsigned int len = paddedData.length();
    for (unsigned int i = 0; i < len; i++) {
        if (paddedData[0] == pad_char)  {
        	paddedData.erase(0, 1);
        } else {
        	return true;
        }
    }
    return true;
}
