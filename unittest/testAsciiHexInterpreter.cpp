#include "AsciiHexInterpreter.h"
#include "ISOUtil.h"
#include "gtest/gtest.h"

class testAsciiHexInterpreter : public ::testing::Test  {
protected:
	testAsciiHexInterpreter() {};
	virtual ~testAsciiHexInterpreter() {};
    virtual void SetUp(){};
    virtual void TearDown(){};
};

TEST_F(testAsciiHexInterpreter, getPackedLength) {
    ASSERT_EQ(AsciiHexInterpreter::LEFT_PADDED_0->getPackedLength(0), 0);
    ASSERT_EQ(AsciiHexInterpreter::LEFT_PADDED_0->getPackedLength(100), 50);
    ASSERT_EQ(AsciiHexInterpreter::LEFT_PADDED_0->getPackedLength(101), 51);
    ASSERT_EQ(AsciiHexInterpreter::LEFT_PADDED_0->getPackedLength(99), 50);

    ASSERT_EQ(AsciiHexInterpreter::LEFT_PADDED_F->getPackedLength(0), 0);
    ASSERT_EQ(AsciiHexInterpreter::LEFT_PADDED_F->getPackedLength(100), 50);
    ASSERT_EQ(AsciiHexInterpreter::LEFT_PADDED_F->getPackedLength(101), 51);
    ASSERT_EQ(AsciiHexInterpreter::LEFT_PADDED_F->getPackedLength(99), 50);

    ASSERT_EQ(AsciiHexInterpreter::RIGHT_PADDED_0->getPackedLength(0), 0);
    ASSERT_EQ(AsciiHexInterpreter::RIGHT_PADDED_0->getPackedLength(100), 50);
    ASSERT_EQ(AsciiHexInterpreter::RIGHT_PADDED_0->getPackedLength(101), 51);
    ASSERT_EQ(AsciiHexInterpreter::RIGHT_PADDED_0->getPackedLength(99), 50);

    ASSERT_EQ(AsciiHexInterpreter::RIGHT_PADDED_F->getPackedLength(0), 0);
    ASSERT_EQ(AsciiHexInterpreter::RIGHT_PADDED_F->getPackedLength(100), 50);
    ASSERT_EQ(AsciiHexInterpreter::RIGHT_PADDED_F->getPackedLength(101), 51);
    ASSERT_EQ(AsciiHexInterpreter::RIGHT_PADDED_F->getPackedLength(99), 50);
}

TEST_F(testAsciiHexInterpreter, interpret) {
	std::string asciiVal_odd("1234567");
	std::string asciiVal_even("12345678");

	ASSERT_STREQ("\x01\x23\x45\x67", AsciiHexInterpreter::LEFT_PADDED_0->interpret(asciiVal_odd).c_str());
	ASSERT_STREQ("\xF1\x23\x45\x67", AsciiHexInterpreter::LEFT_PADDED_F->interpret(asciiVal_odd).c_str());
	ASSERT_STREQ("\x12\x34\x56\x70", AsciiHexInterpreter::RIGHT_PADDED_0->interpret(asciiVal_odd).c_str());
	ASSERT_STREQ("\x12\x34\x56\x7F", AsciiHexInterpreter::RIGHT_PADDED_F->interpret(asciiVal_odd).c_str());

	ASSERT_STREQ("\x12\x34\x56\x78", AsciiHexInterpreter::LEFT_PADDED_0->interpret(asciiVal_even).c_str());
	ASSERT_STREQ("\x12\x34\x56\x78", AsciiHexInterpreter::LEFT_PADDED_F->interpret(asciiVal_even).c_str());
	ASSERT_STREQ("\x12\x34\x56\x78", AsciiHexInterpreter::RIGHT_PADDED_0->interpret(asciiVal_even).c_str());
	ASSERT_STREQ("\x12\x34\x56\x78", AsciiHexInterpreter::RIGHT_PADDED_F->interpret(asciiVal_even).c_str());

	std::string ascii_bin_Val_even("0F0E0D0A0901");
	ASSERT_STREQ("\x0F\x0E\x0D\x0A\x09\x01", AsciiHexInterpreter::LEFT_PADDED_0->interpret(ascii_bin_Val_even).c_str());
	ASSERT_STREQ("\x0F\x0E\x0D\x0A\x09\x01", AsciiHexInterpreter::RIGHT_PADDED_0->interpret(ascii_bin_Val_even).c_str());

	std::string ascii_bin_Val_odd("10F0E0D0A0901");
	ASSERT_STREQ("\x01\x0F\x0E\x0D\x0A\x09\x01", AsciiHexInterpreter::LEFT_PADDED_0->interpret(ascii_bin_Val_odd).c_str());
	ASSERT_STREQ("\x10\xF0\xE0\xD0\xA0\x90\x10", AsciiHexInterpreter::RIGHT_PADDED_0->interpret(ascii_bin_Val_odd).c_str());
}

TEST_F(testAsciiHexInterpreter, uninterpret) {
	std::string bin_Val_even("\x0F\x0E\x0D\x0A\x09\x01\x20", 7);
	ASSERT_STREQ("0F0E0D0A090120", AsciiHexInterpreter::LEFT_PADDED_0->uninterpret(bin_Val_even, 14).c_str());
	ASSERT_STREQ("0F0E0D0A090120", AsciiHexInterpreter::RIGHT_PADDED_0->uninterpret(bin_Val_even, 14).c_str());
	ASSERT_STREQ("F0E0D0A090120", AsciiHexInterpreter::LEFT_PADDED_0->uninterpret(bin_Val_even, 13).c_str());
	ASSERT_STREQ("0F0E0D0A09012", AsciiHexInterpreter::RIGHT_PADDED_0->uninterpret(bin_Val_even, 13).c_str());

	std::string bcdVal_LEFT_PADDED_0("\x01\x23\x45\x67");
	std::string bcdVal_LEFT_PADDED_F("\xF1\x23\x45\x67");
	std::string bcdVal_RIGHT_PADDED_0("\x12\x34\x56\x70");
	std::string bcdVal_RIGHT_PADDED_F("\x12\x34\x56\x7F");
	std::string bcdVal("\x12\x34\x56\x78");

	ASSERT_STREQ("1234567", AsciiHexInterpreter::LEFT_PADDED_0->uninterpret(bcdVal_LEFT_PADDED_0, 7).c_str());
	ASSERT_STREQ("1234567", AsciiHexInterpreter::LEFT_PADDED_F->uninterpret(bcdVal_LEFT_PADDED_F, 7).c_str());
	ASSERT_STREQ("1234567", AsciiHexInterpreter::RIGHT_PADDED_0->uninterpret(bcdVal_RIGHT_PADDED_0, 7).c_str());
	ASSERT_STREQ("1234567", AsciiHexInterpreter::RIGHT_PADDED_F->uninterpret(bcdVal_RIGHT_PADDED_F, 7).c_str());

	ASSERT_STREQ("12345678", AsciiHexInterpreter::LEFT_PADDED_0->uninterpret(bcdVal, 8).c_str());
	ASSERT_STREQ("12345678", AsciiHexInterpreter::LEFT_PADDED_F->uninterpret(bcdVal, 8).c_str());
	ASSERT_STREQ("12345678", AsciiHexInterpreter::RIGHT_PADDED_0->uninterpret(bcdVal, 8).c_str());
	ASSERT_STREQ("12345678", AsciiHexInterpreter::RIGHT_PADDED_F->uninterpret(bcdVal, 8).c_str());
}

