#pragma once

#include <iostream>
#include <string>

class Padder {
public:
	Padder(char pad) : pad_char(pad) {};
	virtual ~Padder() {};

	virtual bool pad(std::string& data, int maxLength) = 0;
	virtual bool unpad(std::string& paddedData) = 0;

protected:
	char pad_char;
};
