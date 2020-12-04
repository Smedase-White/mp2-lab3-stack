#include "stack.h"

#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> s(2));
}

TEST(Stack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(Stack<int> s(MAX_STACK_SIZE + 1));
}

TEST(Stack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> s(-1));
}

TEST(Stack, can_create_copied_stack)
{
	Stack<int> s1(2);

	ASSERT_NO_THROW(Stack<int> s2(s1));
}

TEST(Stack, pop_take_last_element)
{
	Stack<int> s(2);
	s.push(1);
	s.push(2);

	EXPECT_EQ(2, s.pop());
}

TEST(Stack, cant_pop_in_clear_stack)
{
	Stack<int> s(3);
	ASSERT_ANY_THROW(s.pop());
}