#include "NullPadder.h"
#include <iostream>

Padder* NullPadder::INSTANCE = new NullPadder('0');

NullPadder::NullPadder(char pad) : Padder(pad) {
}

NullPadder::~NullPadder() {
}

bool NullPadder::pad(std::string& data, int maxLength) {
    return true;
}

bool NullPadder::unpad(std::string& paddedData) {
    return true;
}
