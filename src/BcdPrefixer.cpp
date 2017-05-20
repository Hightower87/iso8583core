#include "BcdPrefixer.h"

Prefixer* BcdPrefixer::L = new BcdPrefixer(1);
Prefixer* BcdPrefixer::LL = new BcdPrefixer(2);
Prefixer* BcdPrefixer::LLL = new BcdPrefixer(3);

BcdPrefixer::BcdPrefixer(int nDigits) : Prefixer(nDigits) {
}

BcdPrefixer::~BcdPrefixer() {
}

std::string BcdPrefixer::encodeLength(int length) {
	std::string b = "";
	for (int i = getPackedLength() - 1; i >= 0; i--) {
		int twoDigits = length % 100;
		length /= 100;
		b.insert(0, 1, (unsigned char)((twoDigits / 10 << 4) + twoDigits % 10));
	}
	return b;
}

int BcdPrefixer::decodeLength(std::string& b, int offset) {
	int len = 0;
	for (int i = 0; i < nDigits; i++)
	{
		len = 100 * len + ((b[i + offset] & 0xF0) >> 4) * 10 + (b[i + offset] & 0x0F);
	}
	return len;
}

int BcdPrefixer::getPackedLength() {
	return nDigits;
}
