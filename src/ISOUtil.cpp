#include "ISOUtil.h"
#include "stdio.h"
#include "string.h"
#include <algorithm>
#include <stdexcept>

unsigned char a2hex(char hexChar) {
    if (hexChar >= '0') {
        if (hexChar <= '9') return hexChar - '0';
        if (hexChar >= 'a' && hexChar <= 'f') return hexChar - 'a' + 10;
        if (hexChar >= 'A' && hexChar <= 'F') return hexChar - 'A' + 10;
    }
    return 0;
}

unsigned long ascHex(std::string& srcData, unsigned char nBufLen) {
    unsigned long i, index = 0;
    unsigned char b1, b2;
    const char* pAscii = srcData.c_str();
    unsigned char* destBuffer = NULL;
    size_t Asciilen = nBufLen * 2;

    destBuffer = new unsigned char[nBufLen + 1];

    for (i = 0; (i < nBufLen) && (i < Asciilen) ; i++, index++) {
        b1 = a2hex(*pAscii++);
        b2 = a2hex(*pAscii++);
        *(destBuffer + index ) = (b1 << 4) + (b2 << 0);
    }

    // update the formated data
    srcData.clear();
    srcData.append(reinterpret_cast<char*>(destBuffer), nBufLen);
    delete [] destBuffer;
    destBuffer = NULL;
    return (i / 2);
}

unsigned char binBcdB(unsigned char bindata) {
    unsigned char retval;

    retval = bindata / 10;
    retval <<= 4;
    retval |= (bindata % 10);

    return retval;
}

unsigned short binBcdW(unsigned short binData) {
    unsigned char retval[2];
    unsigned char tmp;
    unsigned short *retword;

    // Calculate 100's part of binary word
    retval[0] = binData / 100;

    // Calculate 10's part of word
    retval[1] = binData - (retval[0] * 100);
    tmp = ((retval[1] / 10) * 16);
    retval[1] = (retval[1] % 10) + tmp;

    retword = (unsigned short *) retval;

    return (*retword);
}

unsigned char cvtBin(unsigned char bcdNumber) {
    return (((bcdNumber & 0xF0) >> 4) * 10
            + ((bcdNumber & 0x0F) >> 0) *  1);
}

unsigned int bcdBinW(unsigned char * bcdNumber) {
    return ((cvtBin(bcdNumber[0]) * 100) + (cvtBin(bcdNumber[1])));
}

size_t stringToBCD(std::string & str, size_t len, bool rightJ) {
    unsigned char b1, b2;

    // if odd length and left justified
    bool Odd = false;
    unsigned int index = 0;
    unsigned char* pBuffer = NULL;

    size_t templen = str.length();

    if (0 == templen) {
        return 0;
    }

    // allocate the buffer
    pBuffer = new unsigned char[len + 1];
    memset(pBuffer, 0x00, len + 1);

    // if odd count of digits
    if (templen % 2) {
        Odd = true;
    }

    if (!rightJ) {
        // where to start writing to caller's buffer
        index = 0;
    } else {
        // compute required bytes for BCD digits
        templen =  templen / 2 + ((Odd) ? 1 : 0);

        // find starting point
        index = len - templen;

        // fill in with zeros up to and including start point
        memset(pBuffer, 0, index + 1);

    }

    // convert to BCD
    int i = 0;
    int str_end = str.length();

    while (index < len && i < str_end) {
        // convert to single BCD digit
        b1 = str[i] - 0x30; 		// Char '=' gets translated into '\r' = 0x0D,
        i++;					// a2hex does not do that conversion.

        if (i < str_end) {
            b2 = str[i] - 0x30;
            i++;
        } else {
            if (Odd && !rightJ) {
                b2 = 0x0f;
            } else {
                b2 = 0;
            }
        }
        if (Odd && rightJ) {
            *(pBuffer + index) |= b1;
            index++;
            if (i < str_end) {
                *(pBuffer + index) = (b2 << 4);
            }
        } else {
            *(pBuffer + index) = (b1 << 4) + b2;
            index++;
        }
    }

    // clear the buffer and append the same
    str.clear();
    str.append(reinterpret_cast<char*>(pBuffer), index);
    delete [] pBuffer;
    pBuffer = NULL;
    // index contains total bytes put in caller's buffer
    return index;
}

void trimData(std::string& str, char check) {
    unsigned int  i = 0, len = str.length();
    std::string lstr(str);
    str.clear();
    while (lstr[i] == check) i++;
    str.assign( lstr, i, (len - i));
}

std::string BCDtostring(std::string &bcd, size_t len, bool rightJ) {
	std::string str_ascii = "";
	bool Odd = false;

    if (len % 2) {
        Odd = true;
    }

    int start = Odd && rightJ ? 1 : 0;

	if (bcd.size()) {
		std::string bcd_nibbles = "";
		for (unsigned int i = 0; i < bcd.size(); i++) {
			bcd_nibbles.append(1, static_cast<char>(((bcd[i] & 0xF0) / 0x10) + 0x30));
			bcd_nibbles.append(1, static_cast<char>((bcd[i] & 0x0F) + 0x30));
		}

		for (unsigned int i = start; i < len + start; i++) {
			str_ascii.append(1, bcd_nibbles[i]);
		}
	}
	return str_ascii;
}

std::string asciiToHex(const std::string& input)
{
	std::string input_s = input;
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input_s.length();
    if (len & 1) throw std::invalid_argument("odd value!");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input_s[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input_s[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

std::string hexToAscii(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}
