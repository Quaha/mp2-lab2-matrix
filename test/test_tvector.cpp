#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v1(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v1(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v1(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10, 1);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v1(5);
    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
    }

    TDynamicVector<int> v2(v1);

    EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_create_an_empty_vector)
{
    ASSERT_NO_THROW(TDynamicVector<int> v1);
    ASSERT_NO_THROW(TDynamicVector<int> v2(0));
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v1(5);
    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
    }

    TDynamicVector<int> v2(v1);

    v2[2] = 3;

    EXPECT_NE(v2, v1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4, 4);

  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(5);

    ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(5);

    ASSERT_ANY_THROW(v.at(5));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(5, 5);

    ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v1(5, 1), v2(5, 1);

    ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(5, 5), v2(10, 5);

    v1 = v2;

    EXPECT_EQ(v1.size(), v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(5, 0), v2(10, 1);

    ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v1(5), v2(5);

    for (int i = 0; i < 5; i++) {
        v1[i] = i;
        v2[i] = i;
    }

    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(5);

    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }

    EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(5, 0), v2(10, 0);

    EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(5, 0);

    ASSERT_NO_THROW(v = v + 5);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(5, 0);

    ASSERT_NO_THROW(v = v - 5);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(5, 0);

    ASSERT_NO_THROW(v = v * 5);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(5, 1), v2(5, 3);

    ASSERT_NO_THROW(v1 = v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(5, 4), v2(10, 7);

    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v1(5, 3), v2(5, 10);

    ASSERT_NO_THROW(v1 = v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(5, 63), v2(10, 42);

    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(5, 42), v2(5, 42);

    ASSERT_NO_THROW(v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(5, 42), v2(10, 42);

    ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, can_move_construct_vector)
{
    TDynamicVector<int> v1(5);

    for (int i = 0; i < 5; i++) {
        v1[i] = i;
    }

    ASSERT_NO_THROW(TDynamicVector<int> v2(std::move(v1)));
}

TEST(TDynamicVector, moved_vector_is_empty_after_move)
{
    TDynamicVector<int> v1(5);

    for (int i = 0; i < 5; i++) {
        v1[i] = i;
    }

    TDynamicVector<int> v2(std::move(v1));

    EXPECT_EQ(v1.size(), 0);
}

TEST(TDynamicVector, moved_vector_has_correct_data)
{
    TDynamicVector<int> v1(5);

    for (int i = 0; i < 5; i++) {
        v1[i] = i;
    }

    TDynamicVector<int> v2(std::move(v1));

    EXPECT_EQ(v2[0], 0);
    EXPECT_EQ(v2[4], 4);
}

TEST(TDynamicVector, can_move_assign_vector)
{
    TDynamicVector<int> v1(566), v2(1066);

    for (int i = 0; i < 566; i++) {
        v1[i] = i;
    }

    ASSERT_NO_THROW(v2 = std::move(v1));
}

TEST(TDynamicVector, move_assigned_vector_is_empty_after_move)
{
    TDynamicVector<int> v1(5734), v2(10457);

    for (int i = 0; i < 5734; i++) {
        v1[i] = i;
    }
    v2 = std::move(v1);

    EXPECT_EQ(v1.size(), 0);
}

TEST(TDynamicVector, move_assigned_vector_has_correct_data)
{
    TDynamicVector<int> v1(5235), v2(102362);

    for (int i = 0; i < 5235; i++) {
        v1[i] = i;
    }

    v2 = std::move(v1);

    EXPECT_EQ(v2[0], 0);
    EXPECT_EQ(v2[4], 4);
}

TEST(TDynamicVector, can_add_zero_vector)
{
    TDynamicVector<int> v1(5), zeroVector(5), result;

    for (int i = 0; i < 5; i++) {
        v1[i] = i;
        zeroVector[i] = 0;
    }
    result = v1 + zeroVector;

    EXPECT_EQ(result, v1);
}

TEST(TDynamicVector, can_multiply_vector_by_zero)
{
    TDynamicVector<int> v(5), result;
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    result = v * 0;

    for (int i = 0; i < result.size(); i++) {
        EXPECT_EQ(result[i], 0);
    }
}

TEST(TDynamicVector, can_multiply_vector_by_one)
{
    TDynamicVector<int> v(5), result;
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    result = v * 1;

    EXPECT_EQ(result, v);
}

TEST(TDynamicVector, can_move_assign_to_empty_vector)
{
    TDynamicVector<int> v1(5), v2;

    for (int i = 0; i < 5; i++) {
        v1[i] = i;
    }
    v2 = std::move(v1);

    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v1.size(), 0);
}

TEST(TDynamicVector, compare_vectors_with_different_values_return_false)
{
    TDynamicVector<int> v1(5), v2(5);

    for (int i = 0; i < 5; i++) {
        v1[i] = i;
        v2[i] = i + 1;
    }

    EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_copy_assign_vector)
{
    TDynamicVector<int> v1(5), v2;

    for (int i = 0; i < 5; i++) {
        v1[i] = i;
    }
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_initialize_vector_with_values)
{
    int values[] = { 1, 2, 3, 4, 5 };
    TDynamicVector<int> v(values, 5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(v[i], values[i]);
    }
}
