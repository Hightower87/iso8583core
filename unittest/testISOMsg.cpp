#include "ISOMsg.h"
#include "ISOPackager.h"
#include "ISOUtil.h"
#include "gtest/gtest.h"

class testISOMsg : public ::testing::Test  {
protected:
	testISOMsg() {};
	virtual ~testISOMsg() {};
    virtual void SetUp(){};
    virtual void TearDown(){};
};

TEST_F(testISOMsg, pack) {
	ISOMsg msg;
	msg.setPackager(boost::shared_ptr<ISOBasePackager>(new ISOPackager()));
	msg.setMTI("0200");
	msg.set(2, "123456789");
	std::string out = msg.pack();
	ASSERT_FALSE(out.compare(std::string("\x02\x00\x40\x00\x00\x00\x00\x00\x00\x00\x00\x05\x12\x34\x56\x78\x9F", 17)));
	ASSERT_TRUE(msg.isRequest());
}

TEST_F(testISOMsg, unpack) {
	ISOMsg msg;
	msg.setPackager(boost::shared_ptr<ISOBasePackager>(new ISOPackager()));
	msg.unpack(std::string("\x02\x10\x40\x00\x00\x00\x00\x00\x00\x00\x00\x05\x12\x34\x56\x78\x9F", 17));
	ASSERT_TRUE(msg.hasField(0));
	ASSERT_TRUE(msg.hasField(1));
	ASSERT_TRUE(msg.hasField(2));
	ASSERT_TRUE(msg.isResponse());

	ASSERT_STREQ(msg.getValue(0).c_str(), "0210");
	ASSERT_STREQ(msg.getValue(2).c_str(), "123456789");
}

TEST_F(testISOMsg, equality) {
	ISOMsg msg;
	msg.setPackager(boost::shared_ptr<ISOBasePackager>(new ISOPackager()));
	msg.setMTI("0200");
	msg.set(2, "123456789");
	std::string out = msg.pack();

	ISOMsg msg2;
	msg2.setPackager(boost::shared_ptr<ISOBasePackager>(new ISOPackager()));
	msg2.unpack(out);

	ASSERT_STREQ(msg2.getValue(0).c_str(), "0200");
	ASSERT_STREQ(msg2.getValue(2).c_str(), "123456789");
	ASSERT_STREQ(msg2.pack().c_str(), msg.pack().c_str());
}

