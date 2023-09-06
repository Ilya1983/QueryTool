#include "ConstantValue.h"
#include "pch.h"

ConstantValue::ConstantValue(SpecificValue val)
{
    value = val;
}

ConstantValue::~ConstantValue()
{

}

SpecificValue ConstantValue::get_value(ValueReceiver* values)
{
    return value;
}
