#include "AsciiPrefixer.h"

Prefixer* AsciiPrefixer::L = new AsciiPrefixer(1);
Prefixer* AsciiPrefixer::LL = new AsciiPrefixer(2);
Prefixer* AsciiPrefixer::LLL = new AsciiPrefixer(3);

AsciiPrefixer::AsciiPrefixer(int nDigits) : Prefixer(nDigits) {
}

AsciiPrefixer::~AsciiPrefixer(){
}

std::string AsciiPrefixer::encodeLength(int length) {
	std::string b = "";
    int n = length;
    for (int i = nDigits - 1; i >= 0; i--)
    {
    	//b[i] = (unsigned char)(n % 10 + '0');
    	b.insert(0, 1, (unsigned char)(n % 10 + '0'));
        n /= 10;
    }
    return b;
}

int AsciiPrefixer::decodeLength(std::string& b, int offset) {
    int len = 0;
    for (int i = 0; i < nDigits; i++)
    {
        len = len * 10 + b[i + offset] - (unsigned char)'0';
    }
    return len;
}

int AsciiPrefixer::getPackedLength() {
    return nDigits;
}
