#include "pch.h"
#include "ValueReceiverLib.h"

ValueReceiverLib::ValueReceiverLib()
{
}

ValueReceiverLib::~ValueReceiverLib()
{

}

void ValueReceiverLib::add_or_change_value(std::string key, int value)
{
	values[key] = SpecificValue(value, "", false, SpecificValue::INT);
}

void ValueReceiverLib::add_or_change_value(std::string key, std::string value)
{
	values[key] = SpecificValue(0, value, false, SpecificValue::STRING);
}

void ValueReceiverLib::add_or_change_value(std::string key, bool value)
{
	values[key] = SpecificValue(0, "", value, SpecificValue::BOOL);
}

void ValueReceiverLib::remove_value(std::string key)
{
	values.erase(key);
}

SpecificValue ValueReceiverLib::receive_value(std::string name) const
{
	return values.at(name);
}






