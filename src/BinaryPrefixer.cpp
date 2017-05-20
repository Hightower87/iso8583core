#include "BinaryPrefixer.h"

Prefixer* BinaryPrefixer::L = new BinaryPrefixer(1);
Prefixer* BinaryPrefixer::LL = new BinaryPrefixer(2);
Prefixer* BinaryPrefixer::LLL = new BinaryPrefixer(3);

BinaryPrefixer::BinaryPrefixer(int nDigits) : Prefixer(nDigits) {
}

BinaryPrefixer::~BinaryPrefixer(){
}

std::string BinaryPrefixer::encodeLength(int length) {
	std::string b = "";
	for (int i = nDigits - 1; i >= 0; i--) {
		b.insert(0, std::string(1, (unsigned char)(length & 0xFF)));
		length >>= 8;
	}
	return b;
}

int BinaryPrefixer::decodeLength(std::string& b, int offset) {
	int len = 0;
	for (int i = 0; i < nDigits; i++)
	{
		len = 256 * len + (b[i + offset] & 0xFF);
	}
	return len;
}

int BinaryPrefixer::getPackedLength() {
	return nDigits;
}
