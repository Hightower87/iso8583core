#pragma once

#include "ISOFieldPackagerBase.h"
#include "Padder.h"
#include "Interpreter.h"
#include "Prefixer.h"

class ISOField;

class ISOFieldPackager : public ISOFieldPackagerBase {
public:
	ISOFieldPackager(int len,
			std::string description,
			Padder* padder,
			Interpreter* interpreter,
			Prefixer* prefixer);
	virtual ~ISOFieldPackager();

    virtual int getMaxPackedLength();
    virtual std::string pack (ISOField* c);
    virtual int unpack (ISOField* c, std::string b, int offset);

protected:
    Padder *padder;
    Interpreter *interpreter;
    Prefixer *prefixer;
};

