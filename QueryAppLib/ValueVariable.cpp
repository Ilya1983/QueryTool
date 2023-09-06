#include "ValueVariable.h"
#include "pch.h"

ValueVariable::ValueVariable(std::string name)
{	
	var_name = name;
}

SpecificValue ValueVariable::get_value(ValueReceiver* values)
{
	value = values->receive_value(var_name);
	return value;
}

/*
	if(json_values.contains(var_name) == false)
		throw std::invalid_argument("the json file does not have such a variable");

	std::string type = json_values[var_name].type_name();
	if(type == "boolean")
		value = SpecificValue(0, "", json_values[var_name], SpecificValue::BOOL);
	else
		if(type == "number")
			value = SpecificValue(json_values[var_name], "", false, SpecificValue::INT);
		else
			if(type == "string")
				value = SpecificValue(0, json_values[var_name], false, SpecificValue::STRING);
			else
				throw std::invalid_argument("the variable in the json file is invalid");

	return &value;
	*/
