#include "NullPrefixer.h"
#include "AsciiPrefixer.h"
#include "BcdPrefixer.h"
#include "BinaryPrefixer.h"
#include "BcdInterpreter.h"
#include "gtest/gtest.h"

class testPrefixer : public ::testing::Test  {
protected:
	testPrefixer() {};
	virtual ~testPrefixer() {};
    virtual void SetUp(){};
    virtual void TearDown(){};
};

TEST_F(testPrefixer, encodeLength) {
	ASSERT_STREQ("254", AsciiPrefixer::LLL->encodeLength(254).c_str());
	ASSERT_STREQ("014", AsciiPrefixer::LLL->encodeLength(14).c_str());
	ASSERT_STREQ("001", AsciiPrefixer::LLL->encodeLength(1).c_str());
	ASSERT_STREQ("000", AsciiPrefixer::LLL->encodeLength(0).c_str());

	ASSERT_STREQ("14", AsciiPrefixer::LL->encodeLength(14).c_str());
	ASSERT_STREQ("01", AsciiPrefixer::LL->encodeLength(1).c_str());
	ASSERT_STREQ("00", AsciiPrefixer::LL->encodeLength(0).c_str());

	ASSERT_STREQ("1", AsciiPrefixer::L->encodeLength(1).c_str());
	ASSERT_STREQ("0", AsciiPrefixer::L->encodeLength(0).c_str());

	ASSERT_FALSE(BcdPrefixer::LLL->encodeLength(915250).compare(std::string("\x91\x52\x50", 3)));
	ASSERT_FALSE(BcdPrefixer::LLL->encodeLength(15254).compare(std::string("\x01\x52\x54", 3)));
	ASSERT_FALSE(BcdPrefixer::LLL->encodeLength(1514).compare(std::string("\x00\x15\x14", 3)));
	ASSERT_FALSE(BcdPrefixer::LLL->encodeLength(1).compare(std::string("\x00\x00\x01", 3)));
	ASSERT_FALSE(BcdPrefixer::LLL->encodeLength(0).compare(std::string("\x00\x00\x00", 3)));

	ASSERT_FALSE(BcdPrefixer::LL->encodeLength(1514).compare(std::string("\x15\x14", 2)));
	ASSERT_FALSE(BcdPrefixer::LL->encodeLength(114).compare(std::string("\x01\x14", 2)));
	ASSERT_FALSE(BcdPrefixer::LL->encodeLength(1).compare(std::string("\x00\x01", 2)));
	ASSERT_FALSE(BcdPrefixer::LL->encodeLength(0).compare(std::string("\x00\x00", 2)));

	ASSERT_FALSE(BcdPrefixer::L->encodeLength(14).compare(std::string("\x14", 1)));
	ASSERT_FALSE(BcdPrefixer::L->encodeLength(1).compare(std::string("\x01", 1)));
	ASSERT_FALSE(BcdPrefixer::L->encodeLength(0).compare(std::string("\x00", 1)));

	ASSERT_FALSE(BinaryPrefixer::LLL->encodeLength(9254254).compare(std::string("\x8D\x35\x6E", 3)));
	ASSERT_FALSE(BinaryPrefixer::LLL->encodeLength(254254).compare(std::string("\x03\xE1\x2E", 3)));
	ASSERT_FALSE(BinaryPrefixer::LLL->encodeLength(254).compare(std::string("\x00\x00\xFE", 3)));
	ASSERT_FALSE(BinaryPrefixer::LLL->encodeLength(16).compare(std::string("\x00\x00\x10", 3)));
	ASSERT_FALSE(BinaryPrefixer::LLL->encodeLength(1).compare(std::string("\x00\x00\x01", 3)));
	ASSERT_FALSE(BinaryPrefixer::LLL->encodeLength(0).compare(std::string("\x00\x00\x00", 3)));

	ASSERT_FALSE(BinaryPrefixer::LL->encodeLength(34657).compare(std::string("\x87\x61", 2)));
	ASSERT_FALSE(BinaryPrefixer::LL->encodeLength(1232).compare(std::string("\x04\xD0", 2)));
	ASSERT_FALSE(BinaryPrefixer::LL->encodeLength(1).compare(std::string("\x00\x01", 2)));
	ASSERT_FALSE(BinaryPrefixer::LL->encodeLength(0).compare(std::string("\x00\x00", 2)));

	ASSERT_FALSE(BinaryPrefixer::L->encodeLength(254).compare(std::string("\xFE", 1)));
	ASSERT_FALSE(BinaryPrefixer::L->encodeLength(1).compare(std::string("\x01", 1)));
	ASSERT_FALSE(BinaryPrefixer::L->encodeLength(0).compare(std::string("\x00", 1)));
}

TEST_F(testPrefixer, decodeLength) {
	std::string asciiPrefixer("254");
	ASSERT_EQ(254, AsciiPrefixer::LLL->decodeLength(asciiPrefixer));
	asciiPrefixer = std::string("014");
	ASSERT_EQ(14, AsciiPrefixer::LLL->decodeLength(asciiPrefixer));
	asciiPrefixer = std::string("001");
	ASSERT_EQ(1, AsciiPrefixer::LLL->decodeLength(asciiPrefixer));
	asciiPrefixer = std::string("000");
	ASSERT_EQ(0, AsciiPrefixer::LLL->decodeLength(asciiPrefixer));

	asciiPrefixer = std::string("14");
	ASSERT_EQ(14, AsciiPrefixer::LL->decodeLength(asciiPrefixer));
	asciiPrefixer = std::string("01");
	ASSERT_EQ(1, AsciiPrefixer::LL->decodeLength(asciiPrefixer));
	asciiPrefixer = std::string("00");
	ASSERT_EQ(0, AsciiPrefixer::LL->decodeLength(asciiPrefixer));

	asciiPrefixer = std::string("1");
	ASSERT_EQ(1, AsciiPrefixer::L->decodeLength(asciiPrefixer));
	asciiPrefixer = std::string("0");
	ASSERT_EQ(0, AsciiPrefixer::L->decodeLength(asciiPrefixer));

	std::string bcdPrefixer("\x91\x52\x50", 3);
	ASSERT_EQ(915250, BcdPrefixer::LLL->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x01\x52\x54", 3);
	ASSERT_EQ(15254, BcdPrefixer::LLL->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x00\x15\x14", 3);
	ASSERT_EQ(1514, BcdPrefixer::LLL->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x00\x00\x01", 3);
	ASSERT_EQ(1, BcdPrefixer::LLL->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x00\x00\x00", 3);
	ASSERT_EQ(0, BcdPrefixer::LLL->decodeLength(bcdPrefixer));

	bcdPrefixer = std::string("\x52\x54", 2);
	ASSERT_EQ(5254, BcdPrefixer::LL->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x01\x14", 2);
	ASSERT_EQ(114, BcdPrefixer::LL->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x00\x01", 2);
	ASSERT_EQ(1, BcdPrefixer::LL->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x00\x00", 2);
	ASSERT_EQ(0, BcdPrefixer::LL->decodeLength(bcdPrefixer));

	bcdPrefixer = std::string("\x14", 1);
	ASSERT_EQ(14, BcdPrefixer::L->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x01", 1);
	ASSERT_EQ(1, BcdPrefixer::L->decodeLength(bcdPrefixer));
	bcdPrefixer = std::string("\x00", 1);
	ASSERT_EQ(0, BcdPrefixer::L->decodeLength(bcdPrefixer));

	std::string binaryPrefixer("\x8D\x35\x6E", 3);
	ASSERT_EQ(9254254, BinaryPrefixer::LLL->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x03\xE1\x2E", 3);
	ASSERT_EQ(254254, BinaryPrefixer::LLL->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x00\x00\xFE", 3);
	ASSERT_EQ(254, BinaryPrefixer::LLL->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x00\x00\x10", 3);
	ASSERT_EQ(16, BinaryPrefixer::LLL->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x00\x00\x01", 3);
	ASSERT_EQ(1, BinaryPrefixer::LLL->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x00\x00\x00", 3);
	ASSERT_EQ(0, BinaryPrefixer::LLL->decodeLength(binaryPrefixer));

	binaryPrefixer = std::string("\x87\x61", 2);
	ASSERT_EQ(34657, BinaryPrefixer::LL->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x04\xD0", 2);
	ASSERT_EQ(1232, BinaryPrefixer::LL->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x00\x01", 2);
	ASSERT_EQ(1, BinaryPrefixer::LL->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x00\x00", 2);
	ASSERT_EQ(0, BinaryPrefixer::LL->decodeLength(binaryPrefixer));

	binaryPrefixer = std::string("\xFE", 1);
	ASSERT_EQ(254, BinaryPrefixer::L->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x01", 1);
	ASSERT_EQ(1, BinaryPrefixer::L->decodeLength(binaryPrefixer));
	binaryPrefixer = std::string("\x00", 1);
	ASSERT_EQ(0, BinaryPrefixer::L->decodeLength(binaryPrefixer));
}

