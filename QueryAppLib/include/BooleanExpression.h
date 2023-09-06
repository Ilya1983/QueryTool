#pragma once

#include "Expression.h"

class BooleanExpression : public Expression {
public:
	enum BoolOperator {
		AND,
		OR,
		NOT
	};

	BooleanExpression(Expression *left, Expression *right, BoolOperator op);

	virtual ~BooleanExpression();

	bool get_value(ValueReceiver* values) const override;

private:
	Expression *left_expression;
	Expression *right_expression;
	BoolOperator exp_operator;

};