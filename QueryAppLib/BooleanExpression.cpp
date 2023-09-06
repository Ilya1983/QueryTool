#include "BooleanExpression.h"
#include "pch.h"

BooleanExpression::BooleanExpression(Expression *left, Expression *right, BoolOperator op)
{
    left_expression = left;
    right_expression = right;
    exp_operator = op;
}

BooleanExpression::~BooleanExpression()
{
    delete left_expression;
    delete right_expression;
}

bool BooleanExpression::get_value(ValueReceiver* values) const
{
    bool left_value, right_value;

    switch (exp_operator) {
        case BoolOperator::AND:
            left_value = left_expression->get_value(values);
            right_value = right_expression->get_value(values);

            return left_value && right_value;
        case BoolOperator::OR:
            left_value = left_expression->get_value(values);
            right_value = right_expression->get_value(values);

            return left_value || right_value;
        case BoolOperator::NOT:
            right_value = right_expression->get_value(values);

            return !right_value;
    }

    return false;
}
