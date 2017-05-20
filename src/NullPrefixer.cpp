#include "NullPrefixer.h"

Prefixer* NullPrefixer::INSTANCE = new NullPrefixer();

NullPrefixer::NullPrefixer() : Prefixer(0) {
}

NullPrefixer::~NullPrefixer(){
}

std::string NullPrefixer::encodeLength(int length) {
    return "";
}

int NullPrefixer::decodeLength(std::string& b, int offset) {
    return 0;
}

int NullPrefixer::getPackedLength() {
    return 0;
}
