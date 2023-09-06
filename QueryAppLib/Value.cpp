#include "Value.h"
#include "ConstantValue.h"
#include "pch.h"

SpecificValue Value::get_value(ValueReceiver* values)
{
    return SpecificValue();
}

Value* Value::parse(std::string value_str)
{
    value_str = trim(value_str);
    std::string value_str_low = to_lower_case(value_str);

    if (value_str_low == "true")
        return new ConstantValue(SpecificValue(0, "", true, SpecificValue::BOOL));
    if(value_str_low == "false")
        return new ConstantValue(SpecificValue(0, "", false, SpecificValue::BOOL));

    if (value_str[0] == '"' && value_str[value_str.length() - 1] == '"')
        return new ConstantValue(SpecificValue(0, value_str.substr(1, value_str.length() - 2), false, SpecificValue::STRING));
    
    if (is_number(value_str)) {
        int val_int = std::stoi(value_str);
        return new ConstantValue(SpecificValue(val_int, "", false, SpecificValue::INT));
    }
    
    return new ValueVariable(value_str);
}
