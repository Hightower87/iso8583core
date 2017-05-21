#pragma once
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

class ISOBasePackager;
class ISOField;

class ISOMsg {
public:
	typedef std::map<int, boost::shared_ptr<ISOField> > ISOFieldMap;

	ISOMsg();
	virtual ~ISOMsg();
	ISOMsg(std::string mti);
	void setMTI(std::string mti);
	std::string getMTI();
	void setPackager(boost::shared_ptr<ISOBasePackager> p);
	boost::shared_ptr<ISOBasePackager> getPackager();
	void set(boost::shared_ptr<ISOField> c);
	void set(int fldno, std::string value = "");
	void unset(int fldno);
	bool hasField(int fldno);
	std::string pack();
	int unpack(std::string b);
	boost::shared_ptr<ISOField> getField(int fldno);
	std::string getValue(int fldno);
	bool isRequest();
	bool isResponse();
	ISOFieldMap getChildren();

private:
	void recalcBitMap();
	boost::shared_ptr<ISOBasePackager> packager;
	ISOFieldMap fields;
};
