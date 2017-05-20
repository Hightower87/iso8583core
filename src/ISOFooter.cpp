#include "ISOFooter.h"
#include <boost/crc.hpp>

ISOFooter::~ISOFooter() {
}

ISOFooter::ISOFooter() : footer("") {
}

std::string ISOFooter::pack() {
	return footer;
}

int ISOFooter::unpack(std::string header) {
	this->footer = header;
	return getLength();
}

int ISOFooter::getLength() {
	return footer.size();
}

std::string ISOFooter::getFooter() {
	return footer;
}

int ISOFooter::GetCrc32(const std::string& data) {
    boost::crc_32_type result;
    result.process_bytes(data.data(), data.length());
    return result.checksum();
}
