#include "SpecificValue.h"
#include "pch.h"

SpecificValue::SpecificValue()
{
    value_int = 0;
    value_str = "";
    value_boool = false;
    value_type = ValueType::INT;
}

SpecificValue::SpecificValue(int val_int, std::string val_str, bool val_bool, ValueType type)
{
    value_int = val_int;
    value_str = val_str;
    value_boool = val_bool;
    value_type = type;
}
