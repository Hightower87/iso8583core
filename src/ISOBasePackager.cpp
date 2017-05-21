#include "ISOBasePackager.h"
#include "ISOFieldPackager.h"
#include "ISOFieldPackagerBase.h"
#include "ISOField.h"
#include "ISOMsg.h"
#include "ISOHeader.h"
#include "ISOFooter.h"
#include <string>
#include <stdio.h>

ISOBasePackager::ISOBasePackager() : header(NULL), footer(NULL) {}
ISOBasePackager::~ISOBasePackager() {}

std::string ISOBasePackager::getFieldDescription(ISOMsg* m, int fldNumber) {
	return fieldPackagers[fldNumber]->getDescription();
}

boost::shared_ptr<ISOFieldPackagerBase> ISOBasePackager::getFieldPackager (int fldNumber) {
	return (unsigned int)fldNumber < fieldPackagers.size() ? fieldPackagers[fldNumber] : boost::shared_ptr<ISOFieldPackagerBase>();
}

void ISOBasePackager::setFieldPackager(int fldNumber, boost::shared_ptr<ISOFieldPackagerBase> fieldPackager) {
	fieldPackagers[fldNumber] = fieldPackager;
}

std::string ISOBasePackager::pack(ISOMsg* m) {
	ISOMsg::ISOFieldMap fields = m->getChildren();
	std::string b = "";

	printf("##############################BUILD##############################\n");

	//append header
	if (header != NULL) {
		b.append(header->pack());
	}

	//append fields
	for (int i = 0; i <= 128; i++) {
		if(fields.find(i) != fields.end() && fieldPackagers.find(i) != fieldPackagers.end()) {
			std::string data = fieldPackagers[i]->pack(fields[i]);
			if(data.size()) {
				b.append(data);

				printf("Field [%d] [size:%lu] (%s)\n", i, data.size(), fieldPackagers[i]->getDescription().c_str());
				HEXDUMP(data);
			} else {
				m->unset(i);
			}
		}
	}

	//append footer
	if (footer != NULL) {
		b.append(footer->pack());
	}

	printf("###########################BUILD END#############################\n");

	return b;
}

int ISOBasePackager::unpack(ISOMsg* m, std::string b) {
	int consumed = 0;

	printf("##############################PARSE##############################\n");
	//parse header
	if (header != NULL) {
		int headerSize = header->unpack(b);
		consumed += headerSize;
	}

	//parse fields
	for (int i = 0; i < 128; i++) {
		if(fieldPackagers.find(i) != fieldPackagers.end()) {
			if((unsigned int)consumed >= b.size())
				break;

			boost::shared_ptr<ISOField> field = fieldPackagers[i]->createComponent(i);
			int fieldSize = fieldPackagers[i]->unpack(field, b, consumed);
			if(fieldSize > 0) {
				printf("Field [%d] [size:%d] (%s)\n", field->getFieldNumber(), fieldSize, fieldPackagers[i]->getDescription().c_str());
				HEXDUMP(b.substr(consumed, fieldSize));

				m->set(field);
				consumed += fieldSize;
			}
		}
	}

	//parse footer
	if (footer != NULL) {
		int footerSize = footer->unpack(b);
		consumed += footerSize;
	}

	printf("###########################PARSE END#############################\n");

	return consumed;
}

void ISOBasePackager::setHeader(ISOHeader* header) {
	this->header = header;
}

void ISOBasePackager::setFooter(ISOFooter* footer) {
	this->footer = footer;
}

