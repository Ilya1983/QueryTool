#pragma once

#include <stdexcept>
#include "SpecificValue.h"
#include "utilities.h"
#include "ValueReceiver.h"

class Value {
public:	
	Value() {};
	virtual ~Value() {}

	virtual SpecificValue get_value(ValueReceiver* values);

	static Value* parse(std::string value_str);
};