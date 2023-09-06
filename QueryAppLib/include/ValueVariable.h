#pragma once

#include "Value.h"
#include <string>

class ValueVariable : public Value {
public:
	ValueVariable(std::string name);

	SpecificValue get_value(ValueReceiver* values) override;

private:
	std::string var_name;
	SpecificValue value;
};