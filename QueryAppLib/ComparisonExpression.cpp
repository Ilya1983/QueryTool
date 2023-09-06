#include "ComparisonExpression.h"
#include "pch.h"

ComparisonExpression::ComparisonExpression(Value* left, Value* right, Sign sign)
{

    left_value = left;
    right_value = right;
    expression_sign = sign;
}

ComparisonExpression::~ComparisonExpression()
{
    delete left_value;
    delete right_value;
}

bool ComparisonExpression::get_value(ValueReceiver* values) const
{
    SpecificValue const_left_value = left_value->get_value(values);
    SpecificValue const_right_value = right_value->get_value(values);

    if (const_left_value.value_type != const_right_value.value_type)
        throw std::invalid_argument("can't compare the two arguments");

    switch (const_left_value.value_type) {
    case SpecificValue::INT:
        if (const_left_value.value_int == const_right_value.value_int && expression_sign == EQUALS)
            return true;
        if (const_left_value.value_int < const_right_value.value_int && expression_sign == LESS_THEN)
            return true;
        if (const_left_value.value_int > const_right_value.value_int && expression_sign == GREATER_THEN)
            return true;
        break;
    case SpecificValue::STRING:
        return const_left_value.value_str == const_right_value.value_str;
    case SpecificValue::BOOL:
        return const_left_value.value_boool == const_right_value.value_boool;
    }

    return false;
}
