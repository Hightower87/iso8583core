#include "ISOField.h"

ISOField::ISOField(int n) : fieldNumber(n), value("") {
}

ISOField::ISOField(int n, std::string v) : fieldNumber(n), value(v) {
}

ISOField::~ISOField() {
}

void ISOField::setValue(std::string val) {
	value = val;
}

std::string ISOField::getValue() {
	return value;
}

int ISOField::getFieldNumber() {
	return fieldNumber;
}

void ISOField::setFieldNumber(int n) {
	fieldNumber = n;
}
