#include "pch.h"
#include "ValueReceiverJson.h"

ValueReceiverJson::ValueReceiverJson(json json_values)
{
	values = json_values;
}

ValueReceiverJson::~ValueReceiverJson()
{	
}

SpecificValue ValueReceiverJson::receive_value(std::string name) const
{
	if (values.contains(name) == false)
		throw std::invalid_argument("the json file does not have such a variable");

	std::string type = values[name].type_name();
	if (type == "boolean")
		return SpecificValue(0, "", values[name], SpecificValue::BOOL);
	else
		if (type == "number")
			return SpecificValue(values[name], "", false, SpecificValue::INT);
		else
			if (type == "string")
				return SpecificValue(0, values[name], false, SpecificValue::STRING);
			else
				throw std::invalid_argument("the variable in the json file is invalid");

	return SpecificValue();
}
