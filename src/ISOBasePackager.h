#pragma once

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

class ISOField;
class ISOMsg;
class ISOFieldPackagerBase;
class ISOHeader;
class ISOFooter;

class ISOBasePackager {
public:
	typedef std::map<int, boost::shared_ptr<ISOFieldPackagerBase> > ISOFieldPackagerMap;

	ISOBasePackager();
	virtual ~ISOBasePackager();
	std::string getFieldDescription(ISOMsg* m, int fldNumber);
	boost::shared_ptr<ISOFieldPackagerBase> getFieldPackager (int fldNumber);
	void setFieldPackager(int fldNumber, boost::shared_ptr<ISOFieldPackagerBase> fieldPackager);
	std::string pack(ISOMsg* m);
	int unpack(ISOMsg* m, std::string b);
	void setHeader(ISOHeader* header);
	void setFooter(ISOFooter* footer);

private:
	ISOFieldPackagerMap fieldPackagers;
	ISOHeader* header;
	ISOFooter* footer;
};
