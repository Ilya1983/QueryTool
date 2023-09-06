#pragma once
#include <string>
#include "SpecificValue.h"

class ValueReceiver {
public:
	ValueReceiver() {}
	virtual ~ValueReceiver() {}

	virtual SpecificValue receive_value(std::string name) const = 0;
};
