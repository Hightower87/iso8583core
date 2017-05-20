#include "LeftPadder.h"
#include "RightPadder.h"
#include "NullPadder.h"
#include "gtest/gtest.h"

class testPadder : public ::testing::Test  {
protected:
	testPadder() {};
	virtual ~testPadder() {};
    virtual void SetUp(){};
    virtual void TearDown(){};
};

TEST_F(testPadder, pad) {
	std::string zero_test = "abc";
	RightPadder::ZERO_PADDER->pad(zero_test, 15);
	ASSERT_STREQ("abc000000000000", zero_test.c_str());
	LeftPadder::ZERO_PADDER->pad(zero_test, 30);
	ASSERT_STREQ("000000000000000abc000000000000", zero_test.c_str());
	NullPadder::INSTANCE->pad(zero_test, 12312);
	ASSERT_STREQ("000000000000000abc000000000000", zero_test.c_str());

	std::string space_test = "abc";
	RightPadder::SPACE_PADDER->pad(space_test, 15);
	ASSERT_STREQ("abc            ", space_test.c_str());
	LeftPadder::SPACE_PADDER->pad(space_test, 30);
	ASSERT_STREQ("               abc            ", space_test.c_str());
	NullPadder::INSTANCE->pad(space_test, 12312);
	ASSERT_STREQ("               abc            ", space_test.c_str());
}

TEST_F(testPadder, unpad) {
	std::string zero_test = "000000000000000abc000000000000";
	NullPadder::INSTANCE->unpad(zero_test);
	ASSERT_STREQ("000000000000000abc000000000000", zero_test.c_str());
	RightPadder::ZERO_PADDER->unpad(zero_test);
	ASSERT_STREQ("000000000000000abc", zero_test.c_str());
	LeftPadder::ZERO_PADDER->unpad(zero_test);
	ASSERT_STREQ("abc", zero_test.c_str());

	std::string space_test = "               abc            ";
	NullPadder::INSTANCE->unpad(space_test);
	ASSERT_STREQ("               abc            ", space_test.c_str());
	RightPadder::SPACE_PADDER->unpad(space_test);
	ASSERT_STREQ("               abc", space_test.c_str());
	LeftPadder::SPACE_PADDER->unpad(space_test);
	ASSERT_STREQ("abc", space_test.c_str());
}

