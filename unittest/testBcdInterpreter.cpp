#include "BcdInterpreter.h"
#include "gtest/gtest.h"

class testBCDInterpreter : public ::testing::Test  {
protected:
	testBCDInterpreter() {};
	virtual ~testBCDInterpreter() {};
    virtual void SetUp(){};
    virtual void TearDown(){};
};

TEST_F(testBCDInterpreter, getPackedLength) {
    ASSERT_EQ(BcdInterpreter::LEFT_PADDED_0->getPackedLength(0), 0);
    ASSERT_EQ(BcdInterpreter::LEFT_PADDED_0->getPackedLength(100), 50);
    ASSERT_EQ(BcdInterpreter::LEFT_PADDED_0->getPackedLength(101), 51);
    ASSERT_EQ(BcdInterpreter::LEFT_PADDED_0->getPackedLength(99), 50);

    ASSERT_EQ(BcdInterpreter::LEFT_PADDED_F->getPackedLength(0), 0);
    ASSERT_EQ(BcdInterpreter::LEFT_PADDED_F->getPackedLength(100), 50);
    ASSERT_EQ(BcdInterpreter::LEFT_PADDED_F->getPackedLength(101), 51);
    ASSERT_EQ(BcdInterpreter::LEFT_PADDED_F->getPackedLength(99), 50);

    ASSERT_EQ(BcdInterpreter::RIGHT_PADDED_0->getPackedLength(0), 0);
    ASSERT_EQ(BcdInterpreter::RIGHT_PADDED_0->getPackedLength(100), 50);
    ASSERT_EQ(BcdInterpreter::RIGHT_PADDED_0->getPackedLength(101), 51);
    ASSERT_EQ(BcdInterpreter::RIGHT_PADDED_0->getPackedLength(99), 50);

    ASSERT_EQ(BcdInterpreter::RIGHT_PADDED_F->getPackedLength(0), 0);
    ASSERT_EQ(BcdInterpreter::RIGHT_PADDED_F->getPackedLength(100), 50);
    ASSERT_EQ(BcdInterpreter::RIGHT_PADDED_F->getPackedLength(101), 51);
    ASSERT_EQ(BcdInterpreter::RIGHT_PADDED_F->getPackedLength(99), 50);
}

TEST_F(testBCDInterpreter, interpret) {
	std::string asciiVal_odd("1234567");
	std::string asciiVal_even("12345678");

	ASSERT_STREQ("\x01\x23\x45\x67", BcdInterpreter::LEFT_PADDED_0->interpret(asciiVal_odd).c_str());
	ASSERT_STREQ("\xF1\x23\x45\x67", BcdInterpreter::LEFT_PADDED_F->interpret(asciiVal_odd).c_str());
	ASSERT_STREQ("\x12\x34\x56\x70", BcdInterpreter::RIGHT_PADDED_0->interpret(asciiVal_odd).c_str());
	ASSERT_STREQ("\x12\x34\x56\x7F", BcdInterpreter::RIGHT_PADDED_F->interpret(asciiVal_odd).c_str());

	ASSERT_STREQ("\x12\x34\x56\x78", BcdInterpreter::LEFT_PADDED_0->interpret(asciiVal_even).c_str());
	ASSERT_STREQ("\x12\x34\x56\x78", BcdInterpreter::LEFT_PADDED_F->interpret(asciiVal_even).c_str());
	ASSERT_STREQ("\x12\x34\x56\x78", BcdInterpreter::RIGHT_PADDED_0->interpret(asciiVal_even).c_str());
	ASSERT_STREQ("\x12\x34\x56\x78", BcdInterpreter::RIGHT_PADDED_F->interpret(asciiVal_even).c_str());
}

TEST_F(testBCDInterpreter, uninterpret) {
	std::string bcdVal_LEFT_PADDED_0("\x01\x23\x45\x67");
	std::string bcdVal_LEFT_PADDED_F("\xF1\x23\x45\x67");
	std::string bcdVal_RIGHT_PADDED_0("\x12\x34\x56\x70");
	std::string bcdVal_RIGHT_PADDED_F("\x12\x34\x56\x7F");
	std::string bcdVal("\x12\x34\x56\x78");

	ASSERT_STREQ("1234567", BcdInterpreter::LEFT_PADDED_0->uninterpret(bcdVal_LEFT_PADDED_0, 7).c_str());
	ASSERT_STREQ("1234567", BcdInterpreter::LEFT_PADDED_F->uninterpret(bcdVal_LEFT_PADDED_F, 7).c_str());
	ASSERT_STREQ("1234567", BcdInterpreter::RIGHT_PADDED_0->uninterpret(bcdVal_RIGHT_PADDED_0, 7).c_str());
	ASSERT_STREQ("1234567", BcdInterpreter::RIGHT_PADDED_F->uninterpret(bcdVal_RIGHT_PADDED_F, 7).c_str());

	ASSERT_STREQ("12345678", BcdInterpreter::LEFT_PADDED_0->uninterpret(bcdVal, 8).c_str());
	ASSERT_STREQ("12345678", BcdInterpreter::LEFT_PADDED_F->uninterpret(bcdVal, 8).c_str());
	ASSERT_STREQ("12345678", BcdInterpreter::RIGHT_PADDED_0->uninterpret(bcdVal, 8).c_str());
	ASSERT_STREQ("12345678", BcdInterpreter::RIGHT_PADDED_F->uninterpret(bcdVal, 8).c_str());
}

