#include "ISOFieldPackager.h"
#include "ISOField.h"

ISOFieldPackager::ISOFieldPackager(int len,
		std::string description,
		Padder* padder,
		Interpreter* interpreter,
		Prefixer* prefixer) : ISOFieldPackagerBase(len, description),
								padder(padder),
								interpreter(interpreter),
								prefixer(prefixer) {}

ISOFieldPackager::~ISOFieldPackager() {}

int ISOFieldPackager::getMaxPackedLength() {
	return prefixer->getPackedLength() + interpreter->getPackedLength(getLength());
}

std::string ISOFieldPackager::pack(boost::shared_ptr<ISOField> c) {
	std::string data = "";
	std::string fielddata = c->getValue();

	if (interpreter->getPackedLength(fielddata.size()) > getLength()) {
		return "";
	}
	padder->pad(fielddata, getLength());
	data.append(prefixer->encodeLength(interpreter->getPackedLength(fielddata.size())));
	data.append(interpreter->interpret(fielddata));
	return data;
}

int ISOFieldPackager::unpack(boost::shared_ptr<ISOField> c, std::string b, int offset) {
	int len = prefixer->decodeLength(b, offset);
	if (len == 0) {
		len = interpreter->getPackedLength(getLength());
	}
	int lenLen = prefixer->getPackedLength();
	std::string lenpacked = b.substr(offset + lenLen, len);
	std::string unpacked = interpreter->uninterpret(lenpacked, lenpacked.size());
	c->setValue(unpacked);
	return lenLen + len;
}
