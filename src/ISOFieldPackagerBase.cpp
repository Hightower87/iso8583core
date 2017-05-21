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

boost::shared_ptr<ISOField> ISOFieldPackagerBase::createComponent(int fldno) {
	return boost::shared_ptr<ISOField>(new ISOField (fldno));
}

boost::shared_ptr<ISOField> ISOFieldPackagerBase::createComponent(int fldno, std::string value) {
	return boost::shared_ptr<ISOField>(new ISOField (fldno, value));
}

