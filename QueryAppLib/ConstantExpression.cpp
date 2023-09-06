#include "ConstantExpression.h"
#include "pch.h"

ConstantExpression::ConstantExpression(bool get_value)
{
    expression_value = get_value;
}

ConstantExpression::~ConstantExpression()
{
}

bool ConstantExpression::get_value(ValueReceiver* values) const
{
    return expression_value;
}
