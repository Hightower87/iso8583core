#include <LiteralInterpreter.h>
#include "gtest/gtest.h"

class testAsciiInterpreter : public ::testing::Test  {
protected:
	testAsciiInterpreter() {};
	virtual ~testAsciiInterpreter() {};
    virtual void SetUp(){};
    virtual void TearDown(){};
};

TEST_F(testAsciiInterpreter, getPackedLength) {
    ASSERT_EQ(LiteralInterpreter::INSTANCE->getPackedLength(0), 0);
    ASSERT_EQ(LiteralInterpreter::INSTANCE->getPackedLength(100), 100);
    ASSERT_EQ(LiteralInterpreter::INSTANCE->getPackedLength(101), 101);
    ASSERT_EQ(LiteralInterpreter::INSTANCE->getPackedLength(99), 99);
}

TEST_F(testAsciiInterpreter, interpret) {
	std::string asciiVal_odd("1234567");
	std::string asciiVal_even("12345678");

	ASSERT_STREQ("1234567", LiteralInterpreter::INSTANCE->interpret(asciiVal_odd).c_str());
	ASSERT_STREQ("12345678", LiteralInterpreter::INSTANCE->interpret(asciiVal_even).c_str());
}

TEST_F(testAsciiInterpreter, uninterpret) {
	std::string asciiVal_odd("1234567");
	std::string asciiVal_even("12345678");

	ASSERT_STREQ("1234567", LiteralInterpreter::INSTANCE->uninterpret(asciiVal_odd, 7).c_str());
	ASSERT_STREQ("12345678", LiteralInterpreter::INSTANCE->uninterpret(asciiVal_even, 8).c_str());
}

