#pragma once

#include "Value.h"
#include <string>
#include "SpecificValue.h"

class ConstantValue : public Value {	
public:
	ConstantValue(SpecificValue val);
	
	~ConstantValue();

	SpecificValue get_value(ValueReceiver* values) override;

private:
	SpecificValue value;
};