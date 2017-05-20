#include "ISOFieldPackagerBase.h"
#include "ISOField.h"

ISOFieldPackagerBase::ISOFieldPackagerBase() : len(-1), description("") {}
ISOFieldPackagerBase::ISOFieldPackagerBase(int len, std::string description) : len(len), description(description) {}
ISOFieldPackagerBase::~ISOFieldPackagerBase() {}

std::string ISOFieldPackagerBase::getDescription() {
	return description;
}

void ISOFieldPackagerBase::setDescription(std::string description) {
	this->description = description;
}

int ISOFieldPackagerBase::getLength() {
	return len;
}

void ISOFieldPackagerBase::setLength(int len) {
	this->len = len;
}

ISOField* ISOFieldPackagerBase::createComponent(int fldno) {
	return new ISOField (fldno);
}

ISOField* ISOFieldPackagerBase::createComponent(int fldno, std::string value) {
	return new ISOField (fldno, value);
}

