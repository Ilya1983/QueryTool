#pragma once

#include "Value.h"

class ValueExpression: public Value {
public:
    enum ExpressionOperator {
        Plus,
        Minus,
        Multiplication,
        Division
     };

    ValueExpression();
    ~ValueExpression();

    
};