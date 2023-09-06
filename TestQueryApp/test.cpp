#include <gtest/gtest.h>
#include "Expression.h"
#include "ValueReceiverJson.h"
#include "ValueReceiverLib.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
TEST(SanityTest, TrueTest) {

	json j = json::parse("{}");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("5>4");
	bool value = exp->get_value(&values);
	delete exp;
	 
	EXPECT_TRUE(value);
}

TEST(SanityTest, FalseTest) {

	json j = json::parse("{}");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("5=4");
	bool value = exp->get_value(&values);
	delete exp;

	EXPECT_FALSE(value);
}

TEST(VariableTest, IntTrueTest) {

	json j = json::parse("{\"x\":50 }");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("x=50");
	bool value = exp->get_value(&values);
	delete exp;

	EXPECT_TRUE(value);
}

TEST(VariableTest, StringTrueTest) {

	json j = json::parse("{\"x\":\"aaa\" }");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("x=\"aaa\"");
	bool value = exp->get_value(&values);
	delete exp;

	EXPECT_TRUE(value);
}

TEST(VariableTest, BoolTrueTest) {

	json j = json::parse("{\"x\":false }");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("x=false");
	bool value = exp->get_value(&values);
	delete exp;

	EXPECT_TRUE(value);
}

TEST(ComparisonTest, GreaterThenTest) {

	json j = json::parse("{\"x\":25, \"y\":20}");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("x>y");
	bool value_true = exp->get_value(&values);
	delete exp;
	exp = Expression::parse("y>x");
	bool value_false = exp->get_value(&values);

	EXPECT_TRUE(value_true);
	EXPECT_FALSE(value_false);
}

TEST(ComparisonTest, LessThenTest) {

	json j = json::parse("{\"x\":15, \"y\":20}");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("x<y");
	bool value_true = exp->get_value(&values);
	delete exp;
	exp = Expression::parse("y<x");
	bool value_false = exp->get_value(&values);

	EXPECT_TRUE(value_true);
	EXPECT_FALSE(value_false);
}

TEST(ComparisonTest, EqualsIntTest) {

	json j = json::parse("{\"x\":20, \"y\":20, \"z\":15}");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("x=y");
	bool value_true = exp->get_value(&values);
	delete exp;
	exp = Expression::parse("x=z");
	bool value_false = exp->get_value(&values);

	EXPECT_TRUE(value_true);
	EXPECT_FALSE(value_false);
}

TEST(BooleanTest, OrTest) {

	json j = json::parse("{\"x\":20, \"y\":20, \"z\":15}");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("x=y OR x=z");
	bool value_true = exp->get_value(&values);
	delete exp;
	exp = Expression::parse("x=z OR y=z");
	bool value_false = exp->get_value(&values);

	EXPECT_TRUE(value_true);
	EXPECT_FALSE(value_false);
}

TEST(BooleanTest, AndTest) {

	json j = json::parse("{\"x\":20, \"y\":20, \"z\":15}");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("x=y AND z=15");
	bool value_true = exp->get_value(&values);
	delete exp;
	exp = Expression::parse("x=z AND z=18");
	bool value_false = exp->get_value(&values);

	EXPECT_TRUE(value_true);
	EXPECT_FALSE(value_false);
}

TEST(BooleanTest, NotTest) {

	json j = json::parse("{\"x\":20, \"y\":20, \"z\":15}");
	ValueReceiverJson values(j);

	Expression* exp = Expression::parse("NOT x=z");
	bool value_true = exp->get_value(&values);
	delete exp;
	exp = Expression::parse("NOT x=y");
	bool value_false = exp->get_value(&values);

	EXPECT_TRUE(value_true);
	EXPECT_FALSE(value_false);
}

TEST(ValuesReceiverLibTest, NotTest) {

	ValueReceiverLib values;
	values.add_or_change_value("x", 20);
	values.add_or_change_value("y", 20);
	values.add_or_change_value("z", 15);	

	Expression* exp = Expression::parse("NOT x=z");
	bool value_true = exp->get_value(&values);
	delete exp;
	exp = Expression::parse("NOT x=y");
	bool value_false = exp->get_value(&values);

	EXPECT_TRUE(value_true);
	EXPECT_FALSE(value_false);
}

TEST(ExpressionWithQuotationTest, ParanthesisTest) {

	ValueReceiverLib values;
	values.add_or_change_value("x", 20);
	values.add_or_change_value("y", 20);
	values.add_or_change_value("z", 15);

	Expression* exp = Expression::parse("\"(x=y OR\" = \"(hello\" AND x = z");
	bool value = exp->get_value(&values);

	EXPECT_FALSE(value);
}