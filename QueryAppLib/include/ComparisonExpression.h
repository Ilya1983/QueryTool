#pragma once

#include "Expression.h"
#include "Value.h"

class ComparisonExpression : public Expression {
public:
	enum Sign {
		GREATER_THEN,
		LESS_THEN,
		EQUALS
	};

	ComparisonExpression(Value* left, Value* right, Sign sign);
	~ComparisonExpression();

	bool get_value(ValueReceiver* values) const override;

private:
	Sign expression_sign;
	Value* left_value;
	Value* right_value;

};