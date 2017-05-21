#include "ISOMsg.h"
#include "ISOBasePackager.h"
#include "ISOFieldPackagerBase.h"
#include "ISOField.h"
#include "ISOBitMap.h"
#include <stdio.h>

ISOMsg::ISOMsg() {
}

ISOMsg::~ISOMsg() {
}

ISOMsg::ISOMsg(std::string mti) {
	setMTI(mti);
}

void ISOMsg::setPackager(boost::shared_ptr<ISOBasePackager> p) {
	packager = p;
}

boost::shared_ptr<ISOBasePackager> ISOMsg::getPackager() {
	return packager;
}

void ISOMsg::setMTI(std::string mti) {
	set(0, mti);
}

std::string ISOMsg::getMTI() {
	if (!hasField(0))
		return "";
	return getValue(0);
}

void ISOMsg::set(boost::shared_ptr<ISOField> c) {
	if (c != NULL) {
		int i = c->getFieldNumber();
		fields.insert(std::make_pair<int, boost::shared_ptr<ISOField> >(i, c));
	}
}

void ISOMsg::set(int fldno, std::string value) {
	boost::shared_ptr<ISOFieldPackagerBase> fieldPackager = packager->getFieldPackager(fldno);
	if(fieldPackager.get() !=NULL) {
		set(fieldPackager->createComponent(fldno, value));
	}
}

void ISOMsg::unset(int fldno) {
	fields.erase(fldno);
}

bool ISOMsg::hasField(int fldno) {
	return fields.find(fldno) != fields.end();
}

std::string ISOMsg::pack() {
	recalcBitMap();
	return packager->pack(this);
}

int ISOMsg::unpack(std::string b) {
	return packager->unpack(this, b);
}

boost::shared_ptr<ISOField> ISOMsg::getField(int fldno) {
	if (hasField(fldno))
		return fields[fldno];
	else
		return boost::shared_ptr<ISOField>();

}

std::string ISOMsg::getValue(int fldno) {
	boost::shared_ptr<ISOField> c = getField(fldno);
	return c.get() != NULL ? c->getValue() : "";
}

bool ISOMsg::isRequest() {
	std::string mti = getMTI();
	return mti[2] % 2 == 0;
}

bool ISOMsg::isResponse() {
	return !isRequest();
}

ISOMsg::ISOFieldMap ISOMsg::getChildren() {
	return fields;
}

void ISOMsg::recalcBitMap() {
	boost::shared_ptr<ISOBitMap> bitmap = boost::dynamic_pointer_cast<ISOBitMap>(getField(1));
	if (bitmap.get() == NULL) {
		bitmap = boost::shared_ptr<ISOBitMap>(new ISOBitMap());
		set(bitmap);
	}
	bitmap->reset();

	for (int i = 2; i <= 128; i++) {
		if (getField(i) != NULL) {
			bitmap->setBit(i);
		}
	}
}

