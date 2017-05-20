#pragma once

#include "AsciiHexInterpreter.h"
#include "LiteralInterpreter.h"
#include "ISOFieldPackager.h"
#include "ISOBitMapPackager.h"
#include "LeftPadder.h"
#include "NullPadder.h"
#include "AsciiHexInterpreter.h"
#include "NullPrefixer.h"
#include "BinaryPrefixer.h"
#include "BcdPrefixer.h"
#include "NullPrefixer.h"

/*	Naming Conventions for data
 * 	a:		Alpha, including blanks
 *  n:		Numeric values only (if odd, left '0' nibble padded.)
 *  an:		Alphanumeric
 *  b: 		Binary data
 *	cn: 	BCD, variable length (if odd, right 'f' nibble padded.)
 *	z: 		Tracks 2 and 3 code set as defined in ISO/IEC 7813 and ISO/IEC 4909 respectively
 *	.:		1 digit variable field length indicator.
 *	..: 	2 digit variable field length indicator.
 *	...:	3 digit variable field length indicator.
 */

/*	Naming Conventions for prefixer
 *  Fixed: 	no field length used
 *  LL: 	Where 0 < LL < 100, means two leading digits LL specify the field length of field VAR
 *	LLL: 	Where 0 < LLL < 1000, means three leading digits LLL specify the field length of field VAR
 */

class FIX_n : public ISOFieldPackager {
public:
	FIX_n(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			LeftPadder::ZERO_PADDER,
			AsciiHexInterpreter::LEFT_PADDED_0,
			NullPrefixer::INSTANCE){
	};
	virtual ~FIX_n(){};
};

class FIX_an : public ISOFieldPackager {
public:
	FIX_an(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			LeftPadder::SPACE_PADDER,
			LiteralInterpreter::INSTANCE,
			NullPrefixer::INSTANCE){
	};
	virtual ~FIX_an(){};
};

class FIX_b : public ISOFieldPackager {
public:
	FIX_b(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			LeftPadder::ZERO_PADDER,
			AsciiHexInterpreter::LEFT_PADDED_0,
			NullPrefixer::INSTANCE){
	};
	virtual ~FIX_b(){};
};

class BCDLL_n : public ISOFieldPackager {
public:
	BCDLL_n(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			NullPadder::INSTANCE,
			AsciiHexInterpreter::LEFT_PADDED_0,
			BcdPrefixer::LL){
	};
	virtual ~BCDLL_n(){};
};

class BCDLL_cn : public ISOFieldPackager {
public:
	BCDLL_cn(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			NullPadder::INSTANCE,
			AsciiHexInterpreter::RIGHT_PADDED_F,
			BcdPrefixer::LL){
	};
	virtual ~BCDLL_cn(){};
};

class BCDLL_an : public ISOFieldPackager {
public:
	BCDLL_an(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			NullPadder::INSTANCE,
			LiteralInterpreter::INSTANCE,
			BcdPrefixer::LL){
	};
	virtual ~BCDLL_an(){};
};

class BCDLL_z : public ISOFieldPackager {
public:
	BCDLL_z(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			NullPadder::INSTANCE,
			LiteralInterpreter::INSTANCE,
			BcdPrefixer::LL){
	};
	virtual ~BCDLL_z(){};
};

class BCDLLL_n : public ISOFieldPackager {
public:
	BCDLLL_n(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			NullPadder::INSTANCE,
			AsciiHexInterpreter::LEFT_PADDED_0,
			BcdPrefixer::LLL){
	};
	virtual ~BCDLLL_n(){};
};

class BCDLLL_an : public ISOFieldPackager {
public:
	BCDLLL_an(int len, std::string description) : ISOFieldPackager(
			len,
			description,
			NullPadder::INSTANCE,
			LiteralInterpreter::INSTANCE,
			BcdPrefixer::LLL){
	};
	virtual ~BCDLLL_an(){};
};

