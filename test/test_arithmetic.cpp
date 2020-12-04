#include "arithmetic.h"

#include <gtest.h>

TEST(Calculator, can_create_calculator)
{
	ASSERT_NO_THROW(Calculator c());
}

TEST(Calculator, can_create_calculator_with_expression)
{
	string s = "2+3";
	ASSERT_NO_THROW(Calculator c(s));
}

TEST(Calculator, can_add_expression_to_calculator)
{
	string s = "2+3";
	Calculator c;
	ASSERT_NO_THROW(c.addExpression(s));
}

TEST(Calculator, can_copy_calculator)
{
	string s = "2+3";
	Calculator c1(s);
	ASSERT_NO_THROW(Calculator c2(c1));
}



TEST(Calculator, can_lexical_analysis_correct_expression)
{
	string s = "2+3";
	ASSERT_NO_THROW(Calculator c(s));
}

TEST(Calculator, can_lexical_analysis_expression_with_spaces)
{
	string s = "2 +   3";
	ASSERT_NO_THROW(Calculator c(s));
}

TEST(Calculator, cant_lexical_analysis_expression_with_invalid_synbol)
{
	string s = "2>3";
	ASSERT_ANY_THROW(Calculator c(s));
}

TEST(Calculator, can_lexical_analysis_with_negative_number)
{
	string s = "-2+3";
	ASSERT_NO_THROW(Calculator c(s));
}

TEST(Calculator, lexical_analysis)
{

}



TEST(Calculator, invalid_expression_with_two_operation_in_a_row)
{
	string s = "2+-3";
	Calculator c(s);
	ASSERT_ANY_THROW(c.nextStep());
}

TEST(Calculator, invalid_expression_with_number_after_close_bracket)
{
	string s = "(2+3)4";
	Calculator c(s);
	ASSERT_ANY_THROW(c.nextStep());
}

TEST(Calculator, invalid_expression_with_wrong_number_of_bracket)
{
	string s = "2+(3-4))";
	Calculator c(s);
	ASSERT_ANY_THROW(c.nextStep());
}

TEST(Calculator, invalid_expression_with_wrong_position_of_bracket)
{
	string s = "2+)3-4)";
	Calculator c(s);
	ASSERT_ANY_THROW(c.nextStep());
}



TEST(Calculator, sample_syntactic_analysis)
{
	string s = "2+3";
	Calculator c(s);
	c.nextStep();
	s = "23+";
	EXPECT_EQ(s, c.getString());
}

TEST(Calculator, syntactic_analysis_with_same_operation_minus)
{
	string s = "2-3-4";
	Calculator c(s);
	c.nextStep();
	s = "23-4-";
	EXPECT_EQ(s, c.getString());
}

TEST(Calculator, syntactic_analysis_with_brackets)
{
	string s = "2+(3-4)";
	Calculator c(s);
	c.nextStep();
	s = "234-+";
	EXPECT_EQ(s, c.getString());
}