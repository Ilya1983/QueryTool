#pragma once

#include "Expression.h"

class ConstantExpression : public Expression {
public:
	ConstantExpression(bool get_value);

	~ConstantExpression();

	bool get_value(ValueReceiver* values) const override;

private:
	bool expression_value;

};

