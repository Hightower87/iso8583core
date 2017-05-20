#include "ISOFieldPackagers.h"
#include "ISOField.h"
#include "gtest/gtest.h"

class testISOFieldPackagers : public ::testing::Test  {
protected:
	testISOFieldPackagers() {};
	virtual ~testISOFieldPackagers() {};
    virtual void SetUp(){};
    virtual void TearDown(){};
};

TEST_F(testISOFieldPackagers, FIX_n) {
	ISOFieldPackager* packager = new FIX_n(10, "x");
	ISOField* field = new ISOField(3, "3915213");
	ASSERT_FALSE(packager->pack(field).compare(std::string("\x00\x03\x91\x52\x13", 5)));
}

TEST_F(testISOFieldPackagers, FIX_an) {
	ISOFieldPackager* packager = new FIX_an(10, "x");
	ISOField* field = new ISOField(3, "915213");
	ASSERT_FALSE(packager->pack(field).compare(std::string("    915213")));
}

TEST_F(testISOFieldPackagers, FIX_b) {
	ISOFieldPackager* packager = new FIX_b(10, "x");
	ISOField* field = new ISOField(3, "3F15213");
	ASSERT_FALSE(packager->pack(field).compare(std::string("\x00\x03\xF1\x52\x13", 5)));
}

TEST_F(testISOFieldPackagers, BCDLL_n) {
	ISOFieldPackager* packager = new BCDLL_n(10, "x");
	ISOField* field = new ISOField(3, "3F15213000000000000");
	ASSERT_FALSE(packager->pack(field).compare(std::string("\x00\x10\x03\xF1\x52\x13\x00\x00\x00\x00\x00\x00", 12)));
}

TEST_F(testISOFieldPackagers, BCDLL_cn) {
	ISOFieldPackager* packager = new BCDLL_cn(10, "x");
	ISOField* field = new ISOField(3, "13F1521300000000000");
	ASSERT_FALSE(packager->pack(field).compare(std::string("\x00\x10\x13\xF1\x52\x13\x00\x00\x00\x00\x00\x0F", 12)));
}

TEST_F(testISOFieldPackagers, BCDLL_an) {
	ISOFieldPackager* packager = new BCDLL_an(10, "x");
	ISOField* field = new ISOField(3, std::string("\x13\xF1\x52\x13\x00\x00\x00\x00\x00\x00", 10));
	ASSERT_FALSE(packager->pack(field).compare(std::string("\x00\x10\x13\xF1\x52\x13\x00\x00\x00\x00\x00\x00", 12)));
}

TEST_F(testISOFieldPackagers, BCDLLL_n) {
	ISOFieldPackager* packager = new BCDLLL_n(10, "x");
	ISOField* field = new ISOField(3, "3F15213000000000000");
	ASSERT_FALSE(packager->pack(field).compare(std::string("\x00\x00\x10\x03\xF1\x52\x13\x00\x00\x00\x00\x00\x00", 13)));
}

