#include "RightPadder.h"
#include <iostream>

Padder* RightPadder::SPACE_PADDER = new RightPadder(' ');
Padder* RightPadder::ZERO_PADDER = new RightPadder('0');

RightPadder::RightPadder(char pad) : Padder(pad) {
}

RightPadder::~RightPadder() {
}

bool RightPadder::pad(std::string& data, int maxLength) {
    int len = data.length();

    if (len < maxLength) {
        for (; len < maxLength; len++) {
        	data.append(1, pad_char);
        }
    }
    else if (len > maxLength) {
        return false;
    }
    return true;
}

bool RightPadder::unpad(std::string& paddedData) {
    int len = paddedData.length();
    for (int i = len; i > 0; i--)
    {
        if (paddedData[i - 1] != pad_char)
        {
        	paddedData = paddedData.substr(0, i);
            return true;
        }
    }
    return true;
}

