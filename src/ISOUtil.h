#pragma once

#include <string>
#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

/**
 * @brief string to BCD or hex format conversation
 * Converts a one digit ASCII value, 0-9 or A-F, to
 * a hex value 0-F. Lower case letters are accepted.
 * @param AsciiChar - contains ASCII value
 * @return The equivalent hexadecimal value
 */
unsigned char a2hex(char hexChar);

/**
 * @brief string ASCII to hex format conversation
 * Converts ASCII format numbers (decimal or Hexadecimal) into BCD or hex
 * @param pBuffer the address of the destination field
 * @param nBufLen length of the destination field. The source field is twice as long
 * @return The length of the resulting Hex number in bits. This is useful to check
 * if the conversion operation was successful.
 */
unsigned long ascHex(std::string& srcData, unsigned char nBufLen);

/**
 * @brief Convert Byte From Binary to BCD
 * @param binData binary value to convert
 * @return BCD number converted from binary
 */
unsigned char binBcdB(unsigned char ubBIN);

/**
 * @brief convert Word From Binary to BCD
 * @param binData binary value to convert
 * @return BCD number converted from binary
 */
unsigned short binBcdW(unsigned short uwBIN);

/**
 * @brief converts data to binary value
 * converts a BCD number into a binary number
 * @param binData number to be converted
 * return converted binary value
 */
unsigned char cvtBin(unsigned char bcdNumber);

/**
 * @brief converts 2 byte BCD number to binary integer
 * @param bcdNumber pointer to 2 byte BCD number
 * @return converted binary value
 */
unsigned int bcdBinW(unsigned char * bcdNumber);

/**
 * @brief Converts ASCII string to BCD with justification right(f)/left(0)
 * @param str ASC string to convert
 * @param pBuffer pointer to where BCD data is put
 * @param len max length of pBuffer in bytes, set to length of buffer used on return
 * @param rightJ true to right justify BCD digits in buffer,  unused digits to left
 * are zero filled, full length of pBuffer as specified by length is used false for
 * left justified, if odd number of BCD digits is found then last nibble is set to f
 * @return number of bytes put in buffer
 * @note Buffer should be at least (string length)/2. Add 1 for odd string lengths.
 * otherwise exception occurs. string is expected to contain only numeric characters
 */
size_t stringToBCD(std::string & str, size_t len, bool rightJ);

/**
 * @brief trim the data which is right justified
 * trim the passed check data in the string for all occurrence with check
 * @param str source buffer to be trimmed from
 * @param check data to be trimmed
 */
void trimData(std::string& str, char check);

std::string BCDtostring(std::string &bcd, size_t len, bool rightJ);
std::string asciiToHex(const std::string& input);
std::string hexToAscii(const std::string& input);

template<class Elem, class Traits>
inline void hex_dump(const void* aData, std::size_t aLength, std::basic_ostream<Elem, Traits>& aStream, std::size_t aWidth = 16)
{
	const char* const start = static_cast<const char*>(aData);
	const char* const end = start + aLength;
	const char* line = start;
	while (line != end)
	{
		aStream.width(4);
		aStream.fill('0');
		aStream << std::hex << line - start << " : ";
		std::size_t lineLength = std::min(aWidth, static_cast<std::size_t>(end - line));
		for (std::size_t pass = 1; pass <= 2; ++pass)
		{
			for (const char* next = line; next != end && next != line + aWidth; ++next)
			{
				char ch = *next;
				switch(pass)
				{
				case 1:
					aStream << (ch < 32 ? '.' : ch);
					break;
				case 2:
					if (next != line)
						aStream << " ";
					aStream.width(2);
					aStream.fill('0');
					aStream << std::hex << std::uppercase << static_cast<int>(static_cast<unsigned char>(ch));
					break;
				}
			}
			if (pass == 1 && lineLength != aWidth)
				aStream << std::string(aWidth - lineLength, ' ');
			aStream << " ";
		}
		aStream << std::endl;
		line = line + lineLength;
	}
}

inline void HEXDUMP(std::string r) {
	hex_dump(r.c_str(), r.size(), std::cout);
}

inline void HEXDUMP(std::string r, std::size_t size) {
	hex_dump(r.c_str(), size, std::cout);
}

