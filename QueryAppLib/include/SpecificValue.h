#pragma once

#include <string>

class SpecificValue {
public:
	enum ValueType {
		INT,
		STRING,
		BOOL
	};

	SpecificValue();

	SpecificValue(int val_int, std::string val_str, bool val_bool, ValueType type);

	ValueType value_type;
	int value_int;
	std::string value_str;
	bool value_boool;
};
