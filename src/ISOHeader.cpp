#include "ISOHeader.h"

ISOHeader::~ISOHeader() {
}

ISOHeader::ISOHeader() : header("") {
}

std::string ISOHeader::pack() {
	return header;
}

int ISOHeader::unpack(std::string header) {
	this->header = header;
	return getLength();
}

int ISOHeader::getLength() {
	return header.size();
}

std::string ISOHeader::getHeader() {
	return header;
}
