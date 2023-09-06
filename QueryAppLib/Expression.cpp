#include "Expression.h"
#include "BooleanExpression.h"
#include "ConstantExpression.h"
#include "ComparisonExpression.h"
#include "utilities.h"
#include "pch.h"

Expression* Expression::parse(std::string expression_str)
{
    expression_str = trim(expression_str);

    if (expression_str[0] == '(' && expression_str[expression_str.length() - 1] == ')' && expression_str.find('(', 1) == std::string::npos)
        expression_str = expression_str.substr(1, expression_str.length() - 2);

    std::string expression_str_low = to_lower_case(expression_str);

    std::vector<std::size_t> pos_ands = find_one_of_substrings(expression_str_low, std::vector<std::string>{ " and ", " and(", ")and ", ")and(" });
    std::vector<std::size_t> pos_ors = find_one_of_substrings(expression_str_low, std::vector<std::string>{ " or ", " or(", ")or ", ")or(" });
    std::vector<std::size_t> pos_nots = find_one_of_substrings(expression_str_low, std::vector<std::string>{ "not ", "not("});

    std::vector<std::pair<int, int>> eligible_ranges_by_brackets = find_eligible_ranges_by_brackets(expression_str_low);
    std::vector<std::pair<int, int>> eligible_ranges_by_quotation = find_eligible_ranges_by_quotation_marks(expression_str_low);

    for (std::size_t pos : pos_ors)
        if (is_pos_in_ranges(pos + 1, eligible_ranges_by_brackets) && is_pos_in_ranges(pos + 1, eligible_ranges_by_quotation))
            return new BooleanExpression(parse(expression_str.substr(0, pos + 1)), parse(expression_str.substr(pos + 3)), BooleanExpression::BoolOperator::OR);        
    
    for (std::size_t pos : pos_ands)
        if (is_pos_in_ranges(pos + 1, eligible_ranges_by_brackets) && is_pos_in_ranges(pos + 1, eligible_ranges_by_quotation))
            return new BooleanExpression(parse(expression_str.substr(0, pos + 1)), parse(expression_str.substr(pos + 4)), BooleanExpression::BoolOperator::AND);
    
    for (std::size_t pos : pos_nots)
        if (is_pos_in_ranges(pos + 1, eligible_ranges_by_brackets) && is_pos_in_ranges(pos + 1, eligible_ranges_by_quotation))
            return new BooleanExpression(nullptr, parse(expression_str.substr(3)), BooleanExpression::BoolOperator::NOT);
        
    if (expression_str_low == "true")
        return new ConstantExpression(true);
    if (expression_str_low == "false")
        return new ConstantExpression(false);

    std::vector<std::size_t> pos_greater = find_one_of_substrings(expression_str_low, std::vector<std::string>{">"});
    std::vector<std::size_t> pos_lesser = find_one_of_substrings(expression_str_low, std::vector<std::string>{"<"});;
    std::vector<std::size_t> pos_equals = find_one_of_substrings(expression_str_low, std::vector<std::string>{"="});

    for(std::size_t pos : pos_greater)
        if (is_pos_in_ranges(pos, eligible_ranges_by_quotation))
            return new ComparisonExpression(Value::parse(expression_str.substr(0, pos)), Value::parse(expression_str.substr(pos + 1)), ComparisonExpression::Sign::GREATER_THEN);        

    for (std::size_t pos : pos_lesser)
        if (is_pos_in_ranges(pos, eligible_ranges_by_quotation))
            return new ComparisonExpression(Value::parse(expression_str.substr(0, pos)), Value::parse(expression_str.substr(pos + 1)), ComparisonExpression::Sign::LESS_THEN);

    for (std::size_t pos : pos_equals)
        if (is_pos_in_ranges(pos, eligible_ranges_by_quotation))
            return new ComparisonExpression(Value::parse(expression_str.substr(0, pos)), Value::parse(expression_str.substr(pos + 1)), ComparisonExpression::Sign::EQUALS);
        
    

    throw std::invalid_argument("could not parse the input string");
}
