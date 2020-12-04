#include "stack.h"

#include <gtest.h>

TEST(Queue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(Queue<int> q(2));
}

TEST(Queue, cant_create_too_large_queue)
{
	ASSERT_ANY_THROW(Queue<int> q(MAX_STACK_SIZE + 1));
}

TEST(Queue, cant_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(Queue<int> q(-1));
}

TEST(Queue, can_create_copied_queue)
{
	Queue<int> q1(3);

	ASSERT_NO_THROW(Queue<int> q2(q1));
}

TEST(Stack, pop_take_first_element)
{
	Queue<int> q(3);
	q.push(1);
	q.push(2);

	EXPECT_EQ(1, q.pop());
}

TEST(Queue, cant_pop_in_clear_queue)
{
	Queue<int> q(3);
	ASSERT_ANY_THROW(q.pop());
}