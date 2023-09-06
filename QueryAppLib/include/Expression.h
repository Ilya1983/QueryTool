#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include "ValueReceiver.h"

class Expression {
public:
	virtual  ~Expression() {}

	virtual bool get_value(ValueReceiver* values) const = 0;

	//Can throw the std::invalid_argument exception
	static Expression* parse(std::string expression_str);
};

